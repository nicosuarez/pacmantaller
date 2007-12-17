///////////////////////////////////////////////////////////
//  Elemento.cpp
//  Implementation of the Class Elemento
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "Elemento.h"

Elemento::Elemento( int posicion, Orientacion orientacion ): posicion(posicion), orientacion(orientacion), estado(Aparece) 
{
	
}

Elemento::~Elemento()
{
}


int Elemento::getPosicion()
{
	return this->posicion;
}


Orientacion Elemento::getOrientacion()const
{
	return this->orientacion;
}

Estado Elemento::getEstado()const
{
	return estado;
}

void Elemento::setOrientacion( Orientacion orientacion)
{
	this->orientacion = orientacion;
}

void Elemento::setEstado(Estado estado)
{
	this->estado = estado;
}

/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void Elemento::renderizar(){

}

void Elemento::SetPosicion(int posicion){

	this->posicion = posicion;
}
