///////////////////////////////////////////////////////////
//  ConnectionManager.cpp
//  Implementation of the Class ConnectionManager
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "ConnectionManager.h"


ConnectionManager* ConnectionManager::pConnectionManager = NULL;

ConnectionManager* ConnectionManager::getInstance () 
{
    if (pConnectionManager == NULL)
    {  
    	pConnectionManager = new ConnectionManager(); 
    }
    return pConnectionManager;
}
/*----------------------------------------------------------------------------*/
ConnectionManager::ConnectionManager(int maxJugadores) 
{ 
   this->maxJugadores=maxJugadores;
}
/*----------------------------------------------------------------------------*/
void ConnectionManager::agregarJugador(Jugador jugador){
	
}
/*----------------------------------------------------------------------------*/
void ConnectionManager::enviarMensajes(){

}
/*----------------------------------------------------------------------------*/
Pool ConnectionManager::GetJugadores(){

	return jugadores;
}
/*----------------------------------------------------------------------------*/
void ConnectionManager::quitarJugador(){

}
/*----------------------------------------------------------------------------*/
void ConnectionManager::SetJugadores(Pool newVal){

	jugadores = newVal;
}
/*----------------------------------------------------------------------------*/
