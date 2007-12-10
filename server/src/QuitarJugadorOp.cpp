#include "QuitarJugadorOp.h"

QuitarJugadorOp::QuitarJugadorOp( int idJugador )
{
	this->idJugador = idJugador;
}

QuitarJugadorOp::~QuitarJugadorOp()
{
}

bool QuitarJugadorOp::ejecutar()
{
	Modelo::getInstance()->quitarJugador( idJugador);
	return true;
}
