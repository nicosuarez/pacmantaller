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
Posicion::Posicion(int idVertice,int direccion)
{
	this->idArista = 0;
	this->posicionArista = 0;
	this->direccion = direccion;
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

/**
 * Posicion del personaje en el mapa
 */
void Posicion::SetPosicion(int idVertice,int idArista,int posicionArista,int direccion){

	this->idVertice=idVertice;
	this->idArista=idArista;
	this->direccion=direccion;
	this->posicionArista=posicionArista;
}

/**
 * Posicion en un vertice, sin ninguna arista asignada, no puede avanzar hasta que no se
 * realice un cambio de direccion
 */
void Posicion::SetPosicion(int idVertice,int direccion){

	this->idVertice=idVertice;
	this->idArista=0;
	this->direccion=direccion;
	this->posicionArista=0;
}

bool Posicion::estaEnUnVertice()
{
	if(this->idArista==0 && this->posicionArista==0)
		return true;
	
	if(this->direccion==N_E && this->posicionArista > FIN_ARISTA)
		return true;
		
	if(this->direccion==S_O && this->posicionArista < INICIO_ARISTA)
		return true;
	
	return false;
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

void Posicion::cambiarDireccion()
{
	if(this->direccion==N_E)
		this->direccion=S_O;
	else
		this->direccion = N_E;
}

int Posicion::getPosAristaInicial(int orientacion){
	if(S_O==orientacion)
		return FIN_ARISTA;
	else
		return INICIO_ARISTA;
}

int Posicion::getDireccionInicial(Orientacion orientacion){
	if(orientacion==Norte || orientacion==Este)
		return N_E;
	else
		return S_O;
}




