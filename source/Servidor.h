///////////////////////////////////////////////////////////
//  Servidor.h
//  Implementation of the Class Servidor
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_)
#define EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_

#include "Socket.h"
#include <stdio.h>

typedef unsigned short port_type;

/**
 * Clase que modela el servidor.
 */
class Servidor
{

public:
	Servidor(port_type nro_puerto,int cantParam,char** params,
	        int maxcon=10);
	virtual ~Servidor();
	int ejecutar();
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
	 * Maximo de conexiones
	 */
	unsigned int maxConexiones; 
	/** 
	 * Determina si finalizo en juego.
	 */
	bool finalizoJuego;

};
#endif // !defined(EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_)
