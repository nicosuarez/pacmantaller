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
	Modelo *modelo = Modelo::getInstance();
	if( idJugador == 0 && modelo->GetJugadores().size()>1 )
	{
		Stop *stop = new Stop( PACMAN_SE_DESCONECTO );
		modelo->getDispatcher()->enviarMensaje( stop );
	}
	modelo->quitarJugador( idJugador);
	return true;
}
