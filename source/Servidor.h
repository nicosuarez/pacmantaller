///////////////////////////////////////////////////////////
//  Servidor.h
//  Implementation of the Class Servidor
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_)
#define EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_

#include "Socket.h"
#include "ComenzarJuego.h"
#include "MonitorearEntrada.h"
#include <stdio.h>
#include <string>

#define ERR_MAL_EJECUTADO 2

typedef unsigned short port_type;
using std::string;

/**
 * Clase que modela el servidor.
 */
class Servidor
{

public:
	Servidor(port_type nro_puerto,int cantParam,char** params,
	        int maxcon=10);
	virtual ~Servidor();
	int ejecutar(int argc);
	void validarParametros(int cantParam);
	int parsePuerto(char* cPort);
	
private:
	/**
	 * Puerto donde escucha las conexiones de los jugadores.
	 */
	int port;
	/**
	 *  Socket para escuchar 
	 */
	Socket* skServer;
	/** 
	 * Determina si finalizo en juego.
	 */
	bool finalizoJuego;
	/** 
	 * Determina si hay que cerrar el servidor.
	 */
	bool cerrarServidor;
	/** 
	 * Path del archivo de configuracion.
	 */
	std::string configPath;

};
#endif // !defined(EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_)
