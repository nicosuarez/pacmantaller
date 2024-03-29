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


char* Stop::Serialize()
{
	sizePkt = sizeof(PktStop);
	char* buffer = new char[sizePkt];
	PktStop *pkt = (PktStop*) buffer;
	pkt->version = 0;
	pkt->tipo = Stop::STOP_TYPE;
	pkt->aux = this->razon;
	pkt->puntuacion = Modelo::getInstance()->GetPuntuacion();
	return buffer;
}
