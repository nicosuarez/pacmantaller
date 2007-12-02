///////////////////////////////////////////////////////////
//  Quit.cpp
//  Implementation of the Class Quit
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "Quit.h"


Quit::Quit(){

}



Quit::~Quit(){

}


char* Quit::Serialize()
{
	char* buffer = new char[sizeof(PktCabecera)];
	PktCabecera *pkt = (PktCabecera*) buffer;
	pkt->version = 0;
	pkt->tipo = Quit::QUIT_TYPE;
	pkt->aux = 0;
	return buffer;
}
