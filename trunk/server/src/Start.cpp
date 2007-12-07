///////////////////////////////////////////////////////////
//  Start.cpp
//  Implementation of the Class Start
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#include "Start.h"


Start::Start( int id ):id(id){

}



Start::~Start(){

}

char* Start::Serialize()
{
	sizePkt = sizeof(PktStart);
	char* buffer = new char[sizePkt];
	PktStart *pkt = (PktStart*) buffer;
	pkt->version = 0;
	pkt->tipo = Start::START_TYPE;
	pkt->aux = 0;
	pkt->id = htons(this->id);
	return buffer;
}
