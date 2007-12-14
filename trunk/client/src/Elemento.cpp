///////////////////////////////////////////////////////////
//  Elemento.cpp
//  Implementation of the Class Elemento
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "Elemento.h"

Elemento::Elemento( int posicion, Orientacion orientacion ): posicion(posicion), orientacion(orientacion), estado(Aparece) 
{
	
}

Elemento::Elemento( int posicion, Coordenada coord, Orientacion orientacion ): posicion(posicion), orientacion(orientacion), estado(Aparece), coord(coord)
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

Estado Elemento::getEstado()const
{
	return estado;
}

void Elemento::setOrientacion( Orientacion orientacion)
{
	this->orientacion = orientacion;
}

void Elemento::setEstado( Estado estado)
{
	this->estado = estado;
}

/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void Elemento::renderizar(){

}

void Elemento::SetPosicion(int newVal){

	posicion = newVal;
}

void Elemento::setCoordenada( Coordenada coord) 
{
	this->coord = coord;
}

