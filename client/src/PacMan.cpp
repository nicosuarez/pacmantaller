///////////////////////////////////////////////////////////
//  PacMan.cpp
//  Implementation of the Class PacMan
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#include "PacMan.h"


PacMan::PacMan(){
	this->isPowerUp=false;

	coord = Coordenada(0.0f, 0.0f, 0.0f);
	rotacion = Coordenada(0.0f, 180.0f, -100.0f);	
}

PacMan::PacMan(Posicion& posicion):Personaje(posicion){
	this->isPowerUp=false;
	coord = Coordenada(0.0f, 0.0f, 0.0f);
	rotacion = Coordenada(0.0f, 180.0f, -100.0f);	

}


PacMan::~PacMan(){

}

/**
 * Identificador del rol de personaje
 */
int PacMan::GetRol()const{

	return PacMan::PACMAN_TYPE;
}

/**
 * Velocidad del personaje
 */
int PacMan::GetVelocidad(){

	return velocidadInicial;
}


/**
 * Determina si el pacman se encuentra en el estado powerUp
 */
bool PacMan::IsPowerUp(){

	return isPowerUp;
}


/**
 * Determina si el pacman se encuentra en el estado powerUp
 */
void PacMan::SetPowerUp(bool powerUp){

	isPowerUp = powerUp;
}

bool PacMan::operator==( int tipo )const
{
	return tipo == PACMAN_TYPE;
}


void PacMan::renderizar(){	


}

