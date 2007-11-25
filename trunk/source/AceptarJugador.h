///////////////////////////////////////////////////////////
//  AceptarJugador.h
//  Implementation of the Class AceptarJugador
//  Created on:      21-Nov-2007 23:40:17
///////////////////////////////////////////////////////////

#if !defined(EA_A409CB80_59B3_4ace_A341_2BE007BF9E0C__INCLUDED_)
#define EA_A409CB80_59B3_4ace_A341_2BE007BF9E0C__INCLUDED_

#include "ConnectionManager.h"
#include "Modelo.h"

/**
 * Este thread se encarga de escuchar y aceptar los jugadores.
 */
class AceptarJugador
{
private:
	bool* finalizoJuego;
	Socket* skServer;
public:
	AceptarJugador(Socket* skServer,bool* finalizoJuego);
	virtual ~AceptarJugador();

	Socket* aceptarJugador();
	void agregarJugador(Socket* scliente);
	void main();
	operator bool() const;
	bool seFinalizoElJuego();

};
#endif // !defined(EA_A409CB80_59B3_4ace_A341_2BE007BF9E0C__INCLUDED_)
