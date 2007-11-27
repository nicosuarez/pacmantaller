///////////////////////////////////////////////////////////
//  Stop.cpp
//  Implementation of the Class Stop
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#include "Stop.h"


Stop::Stop( int razon)
{
	this->razon = razon;
}



Stop::~Stop(){

}

int Stop::getTipo()
{
	return TIPO_STOP;
}

char* Stop::Serialize()
{
	char* buffer = new char[sizeof(PktStop)];
	PktStop *pkt = (PktStop*) buffer;
	pkt->version = 0;
	pkt->tipo = TIPO_STOP;
	pkt->aux = this->razon;
	pkt->puntuacion = Modelo::getInstance()->GetPuntuacion();
	return buffer;
}
