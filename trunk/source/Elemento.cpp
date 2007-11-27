///////////////////////////////////////////////////////////
//  Elemento.cpp
//  Implementation of the Class Elemento
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "Elemento.h"


Elemento::Elemento( tipoOrientacion tOrientacion):orientacion(tOrientacion)
{
}

Elemento::~Elemento()
{
}


int Elemento::getPosicion()
{
	return posicion;
}


Orientacion Elemento::getOrientacion()const
{
	return orientacion;
}

void Elemento::setOrientacion( Orientacion orientacion)
{
	this->orientacion = orientacion;
}

/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void Elemento::renderizar(){

}

void Elemento::SetPosicion(int newVal){

	posicion = newVal;
}
