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
	char* buffer = new char[sizeof(PktStart)];
	PktStart *pkt = (PktStart*) buffer;
	pkt->version = 0;
	pkt->tipo = Start::START_TYPE;
	pkt->aux = 0;
	pkt->id = this->id;
	return buffer;
}
