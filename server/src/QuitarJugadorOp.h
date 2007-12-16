#ifndef QUITARJUGADOROP_H_
#define QUITARJUGADOROP_H_

#include "Operacion.h"
#include "Modelo.h"
#include "Stop.h"

class QuitarJugadorOp : public Operacion
{
private:
	int idJugador;
	
public:
	//Constructor
	QuitarJugadorOp( int idJugador );
	
	//Destructor
	virtual ~QuitarJugadorOp();
	
	//Quita al jugador de la lista de jugadores
	bool ejecutar();
};

#endif /*QUITARJUGADOROP_H_*/
