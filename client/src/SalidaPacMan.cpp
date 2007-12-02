///////////////////////////////////////////////////////////
//  SalidaPacMan.cpp
//  Implementation of the Class SalidaPacMan
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "SalidaPacMan.h"


SalidaPacMan::SalidaPacMan( int posicion, Orientacion orientacion = Norte ):Elemento( posicion, orientacion )
{
	
}

SalidaPacMan::~SalidaPacMan(){

}

tipoElemento SalidaPacMan:: getTipo()const
{
	return tSalidaPacman;
}


/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void SalidaPacMan::renderizar(){

}

bool SalidaPacMan::operator==( tipoElemento tipo) const
{
	return tipo == tSalidaPacman;
}
