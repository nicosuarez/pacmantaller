///////////////////////////////////////////////////////////
//  PowerUp.cpp
//  Implementation of the Class PowerUp
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "PowerUp.h"


PowerUp::PowerUp( int posicion, Orientacion orientacion = Norte ):Elemento( posicion, orientacion )
{
	
}


PowerUp::~PowerUp(){

}

tipoElemento PowerUp:: getTipo()const
{
	return tPowerup;
}


/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void PowerUp::renderizar(){

}

bool PowerUp::operator==( tipoElemento tipo) const
{
	return tipo == tPowerup;
}
