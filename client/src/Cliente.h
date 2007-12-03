///////////////////////////////////////////////////////////
//  Cliente.h
//  Implementation of the Class Cliente
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_)
#define EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_

#include "Socket.h"
#include "Modelo.h"
#include "RecibirMensaje.h"
#include "LogResource.h"
#include <string>

typedef unsigned short port_type;
using std::string;

/**
 * Clase que modela el cliente.
 */
class Cliente
{

public:
	Cliente(const string& host,Socket::port_type puerto);
	virtual ~Cliente();
	int ejecutar(int cantArg,char* argv[]);
	
private:
	/**
	 *  Socket para escuchar 
	 */
	Socket* skCliente;
	/** 
	 * Determina si finalizo en juego.
	 */
	bool finalizoJuego;
	/** 
	 * Determina si se cerro el servidor.
	 */
	bool cerrarServidor;
	/**
	 * Hilo que establece conexion con el servidor y permite el intercambio 
	 * de mensajes
	 */
	RecibirMensaje* thrRecibirMensajes;
	/**
	 * Se ejecuta el hilo principal del juego el del modelo.
	 */
	void comenzarJuego(int cantArg,char* argv[]);
	/**
	 * Establece conexion con el servidor y permite el intercambio de mensajes
	 */
	void recibirMensajes();

};
#endif // !defined(EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_)
