///////////////////////////////////////////////////////////
//  PacMan.cpp
//  Implementation of the Class PacMan
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#include "PacMan.h"


PacMan::PacMan(){

}



PacMan::~PacMan(){

}

/**
 * Velocidad del personaje
 */
int PacMan::GetVelocidad(){

	return velocidad;
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
void PacMan::SetPowerUp(bool newVal){

	isPowerUp = newVal;
}

bool PacMan::operator==( int tipo )const
{
	return tipo == PACMAN_TYPE;
}
