///////////////////////////////////////////////////////////
//  Jugador.cpp
//  Implementation of the Class Jugador
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#include "Jugador.h"


Jugador::Jugador(Socket* sk,int idPersonaje,int idJugador){
	this->socket=sk;
	this->idJugador=idJugador;
	this->idPersonaje=idPersonaje;
	this->personaje=NULL;
	this->escucharJugador = new EscucharJugador(sk);
	this->keyPressed=-1;
}
/*----------------------------------------------------------------------------*/
Jugador::~Jugador(){
	this->escucharJugador->join();
	delete this->socket;
	delete this->personaje;
	delete this->escucharJugador;
}
/*----------------------------------------------------------------------------*/
/**
 * Setea el identificador de personaje
 */
void Jugador::SetIdPersonaje(int idPersonaje){
	this->idPersonaje=idPersonaje;
}
/*----------------------------------------------------------------------------*/
/**
 * Personaje el cual representa el jugador.
 */
void Jugador::SetPersonaje(Personaje* personaje){
	this->personaje=personaje;
}
/*----------------------------------------------------------------------------*/
/**
 * Obtiene el identificador de personaje
 */
int Jugador::GetIdPersonaje(){
	return this->idPersonaje;
}
/*----------------------------------------------------------------------------*/
/**
 * Obtiene el personaje el cual representa el jugador.
 */
Personaje* Jugador::getPersonaje(){
	return this->personaje;
}
/*----------------------------------------------------------------------------*/
/**
 * pone a corres el thread escucharJugador, el mismo se pone a recibir los
 * mesnajes del server
 * 
 */
void Jugador::escuchar(){
	this->escucharJugador->run();
}
/*----------------------------------------------------------------------------*/
/**
 * Identificador de jugador
 */
int Jugador::GetIdJugador(){

	return idJugador;
}
/*----------------------------------------------------------------------------*/
/**
 * Socket mediante el cual el jugador mantiene la conexion con el servidor
 */
Socket* Jugador::GetSocket(){

	return socket;
}
/*----------------------------------------------------------------------------*/
/**
 * Identificador de jugador
 */
void Jugador::SetIdJugador(int idJugador){

	this->idJugador = idJugador;
}
/*----------------------------------------------------------------------------*/
/**
 * Socket mediante el cual el jugador mantiene la conexion con el servidor
 */
void Jugador::SetSocket(Socket* socket){

	socket = socket;
}
/*----------------------------------------------------------------------------*/
int Jugador::GetKeyPressed(){
	return this->keyPressed;
}
/*----------------------------------------------------------------------------*/
void Jugador::SetKeyPressed(int keyPressed){
	this->keyPressed=keyPressed;
}


