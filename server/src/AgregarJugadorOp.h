///////////////////////////////////////////////////////////
//  AgregarJugadorOp.h
//  Implementation of the Class AgregarJugadorOp
//  Created on:      21-Nov-2007 23:40:17
///////////////////////////////////////////////////////////

#if !defined(EA_D3BA0CF4_509D_4018_9D76_9DE0FEAE4FB9__INCLUDED_)
#define EA_D3BA0CF4_509D_4018_9D76_9DE0FEAE4FB9__INCLUDED_

#include "Operacion.h"
#include "StartJugador.h"

/**
 * Agrega un jugador a la lista de jugadores.
 */
class AgregarJugadorOp : public Operacion
{
private:
	Jugador* jugador;
	
public:
	AgregarJugadorOp(Jugador* jugador);

	bool ejecutar(Modelo* modelo);

protected:
	void internalProcess();
	bool validarOperacion();

};
#endif // !defined(EA_D3BA0CF4_509D_4018_9D76_9DE0FEAE4FB9__INCLUDED_)
