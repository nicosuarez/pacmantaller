///////////////////////////////////////////////////////////
//  Jugador.cpp
//  Implementation of the Class Jugador
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#include "Jugador.h"


Jugador::Jugador(){

}



Jugador::~Jugador(){

}





/**
 * pone a corres el thread escucharJugador, el mismo se pone a recibir los
 * mesnajes del server
 * 
 */
void Jugador::escuchar(){

}


/**
 * Identificador de jugador
 */
int Jugador::GetIdJugador(){

	return idJugador;
}


/**
 * Socket mediante el cual el jugador mantiene la conexion con el servidor
 */
Socket* Jugador::GetSocket(){

	return socket;
}


/**
 * Identificador de jugador
 */
void Jugador::SetIdJugador(int idJugador){

	this->idJugador = idJugador;
}


/**
 * Socket mediante el cual el jugador mantiene la conexion con el servidor
 */
void Jugador::SetSocket(Socket* socket){

	socket = socket;
}