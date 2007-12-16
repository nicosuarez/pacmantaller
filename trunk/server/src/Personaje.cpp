///////////////////////////////////////////////////////////
//  Personaje.cpp
//  Implementation of the Class Personaje
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "Personaje.h"

class Modelo;

Personaje::Personaje(){
	this->seChocoConPared=false;
}

Personaje::Personaje(Posicion& posicion){
	this->posicion=posicion;
	this->seChocoConPared=false;
}

Personaje::~Personaje(){

}

void Personaje::chocoConPared(bool choco)
{
	this->seChocoConPared=choco;
}

bool Personaje::chocoConPared()
{
	return this->seChocoConPared;
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

	return this->velocidad;
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

	this->velocidad = velocidad;
}

/**
 * Incrementar la velocidad del personaje
 */
void Personaje::incVelocidad(int inc){

	this->velocidad+=inc;
}


