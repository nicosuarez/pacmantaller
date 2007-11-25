///////////////////////////////////////////////////////////
//  AgregarJugadorOp.h
//  Implementation of the Class AgregarJugadorOp
//  Created on:      21-Nov-2007 23:40:17
///////////////////////////////////////////////////////////

#if !defined(EA_D3BA0CF4_509D_4018_9D76_9DE0FEAE4FB9__INCLUDED_)
#define EA_D3BA0CF4_509D_4018_9D76_9DE0FEAE4FB9__INCLUDED_

#include "Thread.h"
#include "Operacion.h"

/**
 * Agrega un jugador a la lista de jugadores.
 */
class AgregarJugadorOp : public Operacion
{

public:
	AgregarJugadorOp();
	virtual ~AgregarJugadorOp();

	virtual bool ejecutar(Modelo* modelo);

protected:
	virtual void internalProcess();
	virtual bool validarOperacion();

};
#endif // !defined(EA_D3BA0CF4_509D_4018_9D76_9DE0FEAE4FB9__INCLUDED_)
