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
	  
	  if(cantParam==3)
	  {
		  this->configPath=params[2]; 
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
	this->validarParametros(argc);
	
	//Se pone a monitorear la entrada por teclado para poder cerrar el server.
	MonitorearEntrada monitor(&cerrarServidor);
	monitor.run();
	
	while(!this->cerrarServidor)
	{
		this->finalizoJuego=false;
		//Comienza el juego.
		ComenzarJuego comenzar(skServer,port,configPath,&finalizoJuego,
				               &cerrarServidor);
		comenzar.run();
	}
	return 0;
}
/*----------------------------------------------------------------------------*/
void Servidor::validarParametros(int cantParam)
{
    if(cantParam!=3)
    {
        std::cout<<"Cantidad de parametros invalido.\n";
        exit(ERR_MAL_EJECUTADO);
    }
}
/*----------------------------------------------------------------------------*/
int Servidor::parsePuerto(char* cPort)
{
    string arg="";
    int iPort;
    arg.assign(cPort);
    std::stringstream ps;
    ps.str(arg);
    ps >> iPort;
    return iPort;
}
