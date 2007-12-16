///////////////////////////////////////////////////////////
//  Dispatcher.cpp
//  Implementation of the Class Dispatcher
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "Dispatcher.h"

Dispatcher::Dispatcher( listJugadores *jugadores, bool *terminoJuego, Mutex *m_jugadores )
{
	this->jugadores = jugadores;
	this->terminoJuego = terminoJuego;
	this->m_jugadores = m_jugadores;
}

Dispatcher::~Dispatcher()
{
}

Jugador* Dispatcher::getJugador(int idJugador)
{
	listJugadores::iterator it;
	for( it = jugadores->begin(); it != jugadores->end(); it++ )
		if((*it)->GetIdJugador() == idJugador )
			return (*it);
	return NULL;
}

void Dispatcher::enviarMensaje( Mensaje* mensaje, int idJugador )
{
	mensaje->SetIdJugador( idJugador );
    m_mensajes.lock();
	mensajes.push(mensaje);
    m_mensajes.unlock();
    //Le avisa al hilo del Dispatcher que hay un mensaje que procesar.
    recibiMensajeEvent.activar();
}
/*----------------------------------------------------------------------------*/
Evento& Dispatcher::getRecibiMensajeEvent()
{
	return this->recibiMensajeEvent;
}
/*----------------------------------------------------------------------------*/
/**
 * Hilo que se encarga de despachar los mensajes de la cola a los jugadores
 * conectados
 */
void Dispatcher::main()
{
	if( mensajes.empty() )
	    this->getRecibiMensajeEvent().esperar();
    while( !(*terminoJuego) || !mensajes.empty() )
    {	
    	m_mensajes.lock();
        Mensaje* msg = mensajes.front();
        if( msg->GetIdJugador() == BROADCAST )
        	this->enviarBroadCast(msg);
        else
        	this->enviarMensajeParticular(msg);
        mensajes.pop();
        m_mensajes.unlock();
        delete msg;
        if( mensajes.empty() && !(*terminoJuego) )
    		this->getRecibiMensajeEvent().esperar();
    }
    std::cout << "Sale del dispatcher\n";
}
/*----------------------------------------------------------------------------*/
void Dispatcher::enviarBroadCast( Mensaje* msg )
{
	listJugadores::iterator it;
	char *buffer = msg->Serialize();
	m_jugadores->lock();
	for( it = jugadores->begin(); it != jugadores->end(); it++ )
    {
        Socket* sk_jugador = (*it)->GetSocket();
        sk_jugador->enviar( buffer, msg->getSize() );
    }
	m_jugadores->unlock();
	delete []buffer;
}
/*----------------------------------------------------------------------------*/
void Dispatcher::enviarMensajeParticular( Mensaje* msg )
{
	//Se envia el mensaje a un jugador en particular.
	Jugador* jugador = getJugador( msg->GetIdJugador() );
	if( jugador != NULL )
	{
		Socket* sk_jugador = jugador->GetSocket();
		char *buffer = msg->Serialize();
		sk_jugador->enviar( buffer, msg->getSize() );
		delete []buffer;
	}
}
/*----------------------------------------------------------------------------*/
