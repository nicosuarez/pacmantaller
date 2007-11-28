///////////////////////////////////////////////////////////
//  Servidor.cpp
//  Implementation of the Class Servidor
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#include "Servidor.h"
#include <sstream>

Servidor::Servidor(int maxcon){
	  this->skServer = new Socket(Config::getInstance()->GetPort(),maxcon);
	  this->finalizoJuego = false;
	  this->cerrarServidor=false;
}
/*----------------------------------------------------------------------------*/
Servidor::~Servidor(){

}
/*----------------------------------------------------------------------------*/
int Servidor::ejecutar(){
	
	//Se pone a monitorear la entrada por teclado para poder cerrar el server.
	MonitorearEntrada monitor(&cerrarServidor);
	monitor.run();
	
	while(!this->cerrarServidor)
	{
		this->finalizoJuego=false;
		//Comienza el juego.
		ComenzarJuego comenzar(skServer,&finalizoJuego,&cerrarServidor);
		comenzar.run();
	}
	return 0;
}
/*----------------------------------------------------------------------------*/

