///////////////////////////////////////////////////////////
//  Personaje.cpp
//  Implementation of the Class Personaje
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "Personaje.h"

class Modelo;

Personaje::Personaje(){

}

Personaje::Personaje(Posicion& posicion){
	this->posicion=posicion;
}

Personaje::~Personaje(){

}

/**
 * Posicion del personaje en el mapa
 */
Posicion* Personaje::GetPosicion(){

	return &posicion;
}


/**
 * Velocidad del personaje
 */
int Personaje::GetVelocidad(){

	return velocidad;
}


/**
 * Identificador de personaje
 */
void Personaje::SetId(int id){

	idPersonaje = id;
}


/**
 * Posicion del personaje en el mapa
 */
void Personaje::SetPosicion(Posicion& posicion){

	this->posicion=posicion;
}

/**
 * Velocidad del personaje
 */
void Personaje::SetVelocidad(int velocidad){

	velocidad = velocidad;
}
