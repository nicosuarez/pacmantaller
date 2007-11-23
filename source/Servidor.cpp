///////////////////////////////////////////////////////////
//  Servidor.cpp
//  Implementation of the Class Servidor
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#include "Servidor.h"


Servidor::Servidor(port_type nro_puerto,int cantParam,char** params,
        int maxcon){
	  this->skServer = new Socket(nro_puerto,maxcon);
	  this->maxConexiones = maxcon;
	  this->finalizoJuego = false;
	  this->port = nro_puerto;
}
/*----------------------------------------------------------------------------*/
Servidor::~Servidor(){

}
/*----------------------------------------------------------------------------*/
int Servidor::ejecutar(){
	return 0;
}
/*----------------------------------------------------------------------------*/
