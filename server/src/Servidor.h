///////////////////////////////////////////////////////////
//  Servidor.h
//  Implementation of the Class Servidor
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_)
#define EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_

#include "Socket.h"
#include "MonitorearEntrada.h"
#include "Modelo.h"
#include "AceptarJugador.h"
#include "ConnectionManager.h"
#include "Parser.h"
#include <stdio.h>
#include <string>

typedef unsigned short port_type;
using std::string;

/**
 * Clase que modela el servidor.
 */
class Servidor
{

public:
	Servidor(int maxcon=10);
	virtual ~Servidor();
	int ejecutar();
	
private:
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
	 * Se ejecuta el hilo principal del juego el del modelo.
	 */
	void comenzarJuego();

	void terminarDeAceptarClientes();

};
#endif // !defined(EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_)
