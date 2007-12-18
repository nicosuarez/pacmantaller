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
	this->terminoJuego = Modelo::getInstance()->getFinalizoJuego();
}

EscucharJugador::~EscucharJugador()
{
}

/**
 * Hilo que se encarga de escuchar los mensajes que el jugador recibe del servidor
 */
void EscucharJugador::main()
{
	int tecla = NONE;
	Modelo *modelo = Modelo::getInstance();
	while( !(*terminoJuego) && tecla != KEY_ESCAPE )
	{
		tecla = recibirMensaje();
		if( (*terminoJuego) )
			return;
		modelo->getJugador( idJugador )->SetKeyPressed( tecla );
	}
}

int EscucharJugador::recibirMensaje()
{
	PktCabecera buffer;
	socket->recibir( (char*)(&buffer), sizeof(PktCabecera) );
	return (int)buffer.aux;
}


int EscucharJugador::getId()
{
	return idJugador;
}
