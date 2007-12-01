///////////////////////////////////////////////////////////
//  Dispatcher.cpp
//  Implementation of the Class Dispatcher
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "Dispatcher.h"


Dispatcher::Dispatcher()
{
}
/*----------------------------------------------------------------------------*/
tListJugadores& Dispatcher::getJugadoresList()
{
	Pool pool=ConnectionManager::getInstance()->GetPool();
	return pool.getJugadoresList();
}
/*----------------------------------------------------------------------------*/
void Dispatcher::enviarMensaje(Mensaje* mensaje,Jugador* jugador)
{
	/*Si el jugador es nulo se acola el mensaje para enviar un broadcast a todos
	*los jugadores de la lista.
	* Si no es NULL se envia un BROADCAST del mensaje a todos los jugadores.
	*/
	if(jugador!=NULL)
		mensaje->SetIdJugador(jugador->GetIdJugador());
		
	mensajes.push(mensaje);
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
    Mutex m_dispacher;
    this->getRecibiMensajeEvent().esperar();
    while(!mensajes.empty())
    {	
        m_dispacher.lock();
        
        Mensaje* msg = mensajes.front();
        if(msg->GetIdJugador()==BROADCAST)
        {
        	this->enviarBroadCast(msg);
        }
        else
        {
        	this->enviarMensajeParticular(msg);
        }
        
        m_dispacher.unlock();
        mensajes.pop();
        if( mensajes.empty() )
            this->getRecibiMensajeEvent().esperar();
    }

}
/*----------------------------------------------------------------------------*/
void Dispatcher::enviarBroadCast(Mensaje* msg)
{
	tListJugadores& jugadores = getJugadoresList();
	itListJugadores it;
	for(it=jugadores.begin(); it!=jugadores.end(); it++ )
    {
        Socket* sk_jugador = (*it)->GetSocket();     
        sk_jugador->enviar(msg->Serialize());
    }
}
/*----------------------------------------------------------------------------*/
void Dispatcher::enviarMensajeParticular(Mensaje* msg)
{
	//Se envia el mensaje a un jugador en particular.
	int idJugador=msg->GetIdJugador();
	Jugador* jugador = ConnectionManager::getInstance()->getJugador(idJugador);
	Socket* sk_jugador = jugador->GetSocket();            
    sk_jugador->enviar(msg->Serialize());
}
/*----------------------------------------------------------------------------*/
