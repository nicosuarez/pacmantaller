///////////////////////////////////////////////////////////
//  StartJugador.cpp
//  Implementation of the Class StartJugador
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////


#include "StartJugador.h"


StartJugador* StartJugador::pStartJugador = NULL;

StartJugador* StartJugador::getInstance() 
{
    if (pStartJugador == NULL)
    {  
    	pStartJugador = new StartJugador(); 
    	pStartJugador->run();
    }
    return pStartJugador;
}
/*----------------------------------------------------------------------------*/
StartJugador::StartJugador(){

}
/*----------------------------------------------------------------------------*/
/**
 * Hilo que se encarga agregar un jugador al juego, dando tiempo para que 
 * muestre el mapa. 
 */
void StartJugador::main(){

	this->esperarRecibirStart();
		
	while(!this->startPlayers.empty())
	{	
		Play* play=getStart();	
		play->join();
		delete play;
		this->desacolar();
		
		/* Espera al proximo jugador para agregarlo al juego */
		this->esperarRecibirStart();
	}
}
/*----------------------------------------------------------------------------*/
void StartJugador::esperarRecibirStart()
{
	if(startPlayers.empty() && !Modelo::getInstance()->seFinalizoElJuego())
	{
		//Espera a recibir operaciones.
		this->getRecibiStartEvent().esperar();
	}
}
/*----------------------------------------------------------------------------*/
Play* StartJugador::desacolar()
{
	Play* play=this->startPlayers.front();
	this->startPlayers.pop();
	return play;
}
/*----------------------------------------------------------------------------*/
Play* StartJugador::getStart()
{
	return this->startPlayers.front();
}
/*----------------------------------------------------------------------------*/
/**
 * Coloca la jugador en la cola en la espera de ingresar al juego.
 */
void StartJugador::agregarStart(Play* play){
	this->startPlayers.push(play);
	/* Avisa al hilo que llego un nuevo jugador a insertar al juego */
	this->getRecibiStartEvent().activar(); 
}

