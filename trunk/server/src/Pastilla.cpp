///////////////////////////////////////////////////////////
//  Pastilla.cpp
//  Implementation of the Class Pastilla
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "Pastilla.h"


Pastilla::Pastilla( int posicion, Orientacion orientacion ):Elemento( posicion, orientacion )
{

}


Pastilla::~Pastilla()
{

}


tipoElemento Pastilla::getTipo()const
{
	return tPastilla;
}

/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void Pastilla::renderizar(){

}

bool Pastilla::operator==( tipoElemento tipo) const
{
	return tipo == tPastilla; 
}
