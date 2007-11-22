///////////////////////////////////////////////////////////
//  CerrarServidor.h
//  Implementation of the Class CerrarServidor
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_F88EAA8B_43FD_4d3a_825C_387F3C6CC317__INCLUDED_)
#define EA_F88EAA8B_43FD_4d3a_825C_387F3C6CC317__INCLUDED_

/**
 * Hilo que se encarga de cerrar el servidor, no permitiendo aceptar mas
 * conexiones, una vez que termino el juego (finaliza el hilo del modelo)
 */
class CerrarServidor
{

public:
	CerrarServidor();
	virtual ~CerrarServidor();

	void main();

private:
	/**
	 * Indica si termino el juego o no.
	 */
	bool* finalizoJuego;
	/**
	 * Puerto donde el servidor escucha los conexiones
	 */
	int port;

};
#endif // !defined(EA_F88EAA8B_43FD_4d3a_825C_387F3C6CC317__INCLUDED_)
