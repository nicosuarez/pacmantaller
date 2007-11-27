///////////////////////////////////////////////////////////
//  Posicion.cpp
//  Implementation of the Class Posicion
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "Posicion.h"


Posicion::Posicion()
{
}

Posicion::Posicion( int idArista, int posicionArista, Orientacion direccion )
{
	this->idArista = idArista;
	this->posicionArista = posicionArista;
	this->direccion = direccion;
}

Posicion::~Posicion(){

}

int Posicion::getArista()const
{
	return idArista;
}

int Posicion::getPosicionArista()const
{
	return posicionArista;
}

Orientacion Posicion::getDireccion()
{
	return direccion;
}

void Posicion::setArista( int idArista )
{
	this->idArista = idArista;
}

void Posicion::setPosicionArista( int posicionArista )
{
	this->posicionArista = posicionArista;
}

void Posicion::setDireccion( Orientacion orientacion )
{
	this->direccion = direccion;
}
