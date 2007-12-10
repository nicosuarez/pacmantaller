///////////////////////////////////////////////////////////
//  EscucharJugador.cpp
//  Implementation of the Class EscucharJugador
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#include "EscucharJugador.h"


EscucharJugador::EscucharJugador( int idJugador, Socket* socket )
{
	this->idJugador = idJugador;
	this->socket = socket;	
	this->terminoJuego = false;
}

EscucharJugador::~EscucharJugador()
{
}

/**
 * Hilo que se encarga de escuchar los mensajes que el jugador recibe del servidor
 */
void EscucharJugador::main()
{
	while( !terminoJuego )
	{
		int tecla = recibirMensaje();
		if( tecla == KEY_ESC )
		{
			QuitarJugadorOp *quitarJugador = new QuitarJugadorOp( idJugador );
			Modelo::getInstance()->agregarOperacion( quitarJugador );
			return;
		}
		else
			Modelo::getInstance()->getJugador( idJugador )->SetKeyPressed( tecla );
	}
}

int EscucharJugador::recibirMensaje()
{
	PktCabecera buffer;
	socket->recibir( (char*)(&buffer), sizeof(PktCabecera) );
	return (int)buffer.aux;
}

void EscucharJugador::setTerminoJuego( bool terminoJuego )
{
	this->terminoJuego = terminoJuego;	
}
