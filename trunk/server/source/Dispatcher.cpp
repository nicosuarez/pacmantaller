///////////////////////////////////////////////////////////
//  Dispatcher.cpp
//  Implementation of the Class Dispatcher
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "Dispatcher.h"


Dispatcher::Dispatcher(Mutex* m_dispacher)
{
    this->m_dispacher=m_dispacher;
}
/*----------------------------------------------------------------------------*/
tListJugadores& Dispatcher::getJugadoresList()
{
	Pool pool=ConnectionManager::getInstance()->GetPool();
	return pool.getJugadoresList();
}
/*----------------------------------------------------------------------------*/
void Dispatcher::enviarMensaje(Mensaje* mensaje)
{
    mensajes.push(mensaje);
    //Le avisa al hilo del Dispatcher que hay un mensaje que procesar.
    recibiMensajeEvent.activar();
}
/*----------------------------------------------------------------------------*/
Evento& Dispatcher::getRecibiMensajeEvent(){return this->recibiMensajeEvent;};
/*----------------------------------------------------------------------------*/
/**
 * Hilo que se encarga de despachar los mensajes de la cola a todos los jugadores
 * conectados
 */
void Dispatcher::main()
{
	tListJugadores& jugadores = getJugadoresList();
    this->getRecibiMensajeEvent().esperar();
    while(!mensajes.empty())
    {
    	itListJugadores it;
        m_dispacher->lock();
        for(it=jugadores.begin(); it!=jugadores.end(); it++ )
        {
            Socket* sk_jugador = (*it)->GetSocket();
            Mensaje* msg = mensajes.front();
            sk_jugador->enviar(msg->Serialize());
        }
        m_dispacher->unlock();
        mensajes.pop();
        if( mensajes.empty() )
            this->getRecibiMensajeEvent().esperar();
    }

}
/*----------------------------------------------------------------------------*/
