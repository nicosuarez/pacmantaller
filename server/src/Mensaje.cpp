///////////////////////////////////////////////////////////
//  Mensaje.cpp
//  Implementation of the Class Mensaje
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#include "Mensaje.h"


Mensaje::Mensaje(){
	this->idJugador=BROADCAST;
}

Mensaje::~Mensaje(){

}

int Mensaje::GetIdJugador()
{
	return this->idJugador;
}

void Mensaje::SetIdJugador(int id){
	this->idJugador=id;
}

int Mensaje::getSize()const
{
	return sizePkt;
}
