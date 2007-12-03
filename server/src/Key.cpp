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

char* Key::Serialize()
{
	sizePkt = sizeof(PktCabecera);
	char* buffer = new char[sizePkt];
	PktCabecera *pkt = (PktCabecera*) buffer;
	pkt->version = 0;
	pkt->tipo = Key::KEY_TYPE;
	pkt->aux = this->key;
	return buffer;
}
