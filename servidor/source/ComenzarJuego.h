///////////////////////////////////////////////////////////
//  ComenzarJuego.h
//  Implementation of the Class ComenzarJuego
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_F88EAA8B_43FD_4d3a_825C_387F3C6CC317__INCLUDED_)
#define EA_F88EAA8B_43FD_4d3a_825C_387F3C6CC317__INCLUDED_

#include "Thread.h"
#include "Modelo.h"
#include "AceptarJugador.h"
#include "ConnectionManager.h"
#include "Parser.h"
#include <string>

typedef bool* pBool;
using std::string;

/**
 * Hilo que se encarga poner a ejecutar el juego.
 */
class ComenzarJuego: public Thread
{

public:
	ComenzarJuego(Socket* skServer,pBool finalizoJuego,pBool cerrarServidor);
	virtual ~ComenzarJuego();

	void main();
	void terminarDeAceptarClientes();
private:
	/**
	 * Indica si termino el juego o no.
	 */
	pBool finalizoJuego;
	/**
	 * Indica si el servidor de cerror o no.
	 */
	pBool cerrarServidor;
	/**
	 * Socket por el cual el servidor escucha a los jugadores.
	 */
	Socket* skServer;

};
#endif // !defined(EA_F88EAA8B_43FD_4d3a_825C_387F3C6CC317__INCLUDED_)
