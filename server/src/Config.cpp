///////////////////////////////////////////////////////////
//  Config.cpp
//  Implementation of the Class Config
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "Config.h"


Config* Config::pConfig = NULL;

/**
 * Se obtiene la instancia creada por el metodo setInstance
 */
Config* Config::getInstance () 
{
    return pConfig;
}

/**
 * Se setea una unica instancia de la configuracion.
 */
void Config::setInstance(string mundoXmlPath,int port,int minJugadores,
		int maxJugadores,bool com_fantasmas,int vidas,string archivoLog)
{
	if (pConfig == NULL)
    {  
		pConfig = new Config(mundoXmlPath,port,minJugadores,
				maxJugadores,com_fantasmas,vidas,archivoLog);
    }
}

Config::Config(string mundoXmlPath,int port,size_t minJugadores,size_t maxJugadores,
	           bool com_fantasmas,int vidas,string archivoLog){
	this->mundoXmlPath=mundoXmlPath;
	this->port=port;
	this->minJugadores=minJugadores;
	this->maxJugadores=maxJugadores;
	this->com_fantasmas=com_fantasmas;
	this->vidas=vidas;
	this->archivoLog=archivoLog;
}

