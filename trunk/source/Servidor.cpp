///////////////////////////////////////////////////////////
//  Servidor.cpp
//  Implementation of the Class Servidor
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#include "Servidor.h"
#include <sstream>

Servidor::Servidor(port_type nro_puerto,int cantParam,char** params,
        int maxcon){
	  this->skServer = new Socket(nro_puerto,maxcon);
	  this->finalizoJuego = false;
	  this->port = nro_puerto;
	  this->cerrarServidor=false;
	  
	  if(cantParam==2)
	  {
		  this->configPath=params[1]; 
	  }
	  else
	  {
		  this->configPath=""; 
	  }
}
/*----------------------------------------------------------------------------*/
Servidor::~Servidor(){

}
/*----------------------------------------------------------------------------*/
int Servidor::ejecutar(int argc){
	
	//Se validan los paramentros de entrada.
	Parser::validarParametros(argc);
	
	//Se pone a monitorear la entrada por teclado para poder cerrar el server.
	MonitorearEntrada monitor(&cerrarServidor);
	monitor.run();
	
	while(!this->cerrarServidor)
	{
		this->finalizoJuego=false;
		//Comienza el juego.
		ComenzarJuego comenzar(skServer,configPath,&finalizoJuego,
				               &cerrarServidor);
		comenzar.run();
	}
	return 0;
}
/*----------------------------------------------------------------------------*/

