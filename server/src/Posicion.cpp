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
	this->direccion = N_E;
	this->idVertice=0;
}

//Posiciona en una arista
Posicion::Posicion(int idVertice,int idArista,int posicionArista,int direccion)
{
	this->idArista = idArista;
	this->posicionArista = posicionArista;
	this->direccion = direccion;
	this->idVertice=idVertice;
}

//Posiciona en un vertice
Posicion::Posicion(int idVertice)
{
	this->idArista = 0;
	this->posicionArista = 0;
	this->direccion = N_E;
	this->idVertice=idVertice;
}

Posicion::Posicion( const Posicion &posicion )
{
	this->idArista = posicion.getArista();
	this->posicionArista = posicion.getPosicionArista();
	this->direccion = posicion.getDireccion();
	this->idVertice = posicion.getVertice();
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

void Posicion::setVertice( int idVertice )
{
	this->idVertice = idVertice;
}

void Posicion::operator=( const Posicion &posicion )
{
	this->idVertice=posicion.getVertice();
	this->idArista = posicion.getArista();
	this->posicionArista = posicion.getPosicionArista();
	this->direccion = posicion.getDireccion();
}
