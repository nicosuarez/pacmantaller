///////////////////////////////////////////////////////////
//  Posicion.cpp
//  Implementation of the Class Posicion
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "Posicion.h"


Posicion::Posicion()
{
	this->idArista = 0;
	this->posicionArista = 0;
	this->direccion = 0;
	this->idVertice=0;
}

Posicion::Posicion(int idArista,int posicionArista,int direccion,int idVertice)
{
	this->idArista = idArista;
	this->posicionArista = posicionArista;
	this->direccion = direccion;
	this->idVertice=idVertice;
}

Posicion::Posicion( const Posicion &posicion )
{
	this->idArista = posicion.getArista();
	this->posicionArista = posicion.getPosicionArista();
	this->direccion = posicion.getDireccion();
}

Posicion::~Posicion(){

}

int Posicion::getArista()const
{
	return idArista;
}

int Posicion::getVertice()const
{
	return idVertice;
}

int Posicion::getPosicionArista()const
{
	return posicionArista;
}

int Posicion::getDireccion()const
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

void Posicion::setDireccion( int direccion )
{
	this->direccion = direccion;
}

void Posicion::operator=( const Posicion &posicion )
{
	this->idArista = posicion.getArista();
	this->posicionArista = posicion.getPosicionArista();
	this->direccion = posicion.getDireccion();
}
