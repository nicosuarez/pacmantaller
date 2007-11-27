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


int Start::getTipo()
{
	return TIPO_START;
}


char* Start::Serialize()
{
	char* buffer = new char[sizeof(PktStart)];
	PktStart *pkt = (PktStart*) buffer;
	pkt->version = 0;
	pkt->tipo = TIPO_START;
	pkt->aux = 0;
	pkt->id = this->id;
	return buffer;
}
