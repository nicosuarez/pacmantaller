///////////////////////////////////////////////////////////
//  Key.cpp
//  Implementation of the Class Key
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#include "Key.h"


Key::Key( int key )
{
	this->key = key;
}



Key::~Key(){

}


int Key::getTipo()
{
	return TIPO_KEY;
}


char* Key::Serialize()
{
	char* buffer = new char[sizeof(PktCabecera)];
	PktCabecera *pkt = (PktCabecera*) buffer;
	pkt->version = 0;
	pkt->tipo = TIPO_KEY;
	pkt->aux = this->key;
	return buffer;
}
