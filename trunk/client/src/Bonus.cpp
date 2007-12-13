///////////////////////////////////////////////////////////
//  Bonus.cpp
//  Implementation of the Class Bonus
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "Bonus.h"


Bonus::Bonus( int posicion, Orientacion orientacion): Elemento( posicion, orientacion )
{

}



Bonus::~Bonus(){

}

tipoElemento Bonus::getTipo()const
{
	return tBonus;
}

/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void Bonus::renderizar(){

}

bool Bonus::operator==( tipoElemento tipo) const
{
	return tipo == tBonus;
}
