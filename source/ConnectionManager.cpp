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
   this->asignarId=0;
}
/*----------------------------------------------------------------------------*/

void ConnectionManager::agregarJugador(Jugador* jugador){
	//Se le asigna un id unico.
	jugador->SetIdJugador(this->asignarId);
	//Se agrega a la lista de jugadores
	this->pool.getJugadoresList().push_back(jugador);
	//Se pone a escuchar el socket del jugador
	jugador->escucharJugador->run();
	//Se incrementa el id para asignar al proximo jugador.
	this->asignarId++;
}
/*----------------------------------------------------------------------------*/
void ConnectionManager::enviarMensaje(){

}
/*----------------------------------------------------------------------------*/
Pool& ConnectionManager::GetPool(){
	return pool;
}
/*----------------------------------------------------------------------------*/
void ConnectionManager::quitarJugador(int idJugador){
	
	tListJugadores jugadores=this->pool.getJugadoresList();
	itListJugadores it;
	
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		Jugador* jugador = *it;
		if(jugador->GetIdJugador()==idJugador)
		{
			jugadores.erase(it);
		}
	}
}
