///////////////////////////////////////////////////////////
//  Personaje.cpp
//  Implementation of the Class Personaje
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "Personaje.h"


Personaje::Personaje(){

}



Personaje::~Personaje(){

}





/**
 * Identificador de personaje
 */
int Personaje::GetId(){

	return idPersonaje;
}


/**
 * Posicion del personaje en el mapa
 */
Posicion Personaje::GetPosicion(){

	return posicion;
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
void Personaje::SetId(int newVal){

	idPersonaje = newVal;
}


/**
 * Posicion del personaje en el mapa
 */
void Personaje::SetPosicion(Posicion newVal){

	posicion = newVal;
}


/**
 * Velocidad del personaje
 */
void Personaje::SetVelocidad(int newVal){

	velocidad = newVal;
}