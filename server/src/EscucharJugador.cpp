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
	
	while( !(*terminoJuego) )
	{
		int tecla = recibirMensaje();
		if( (*terminoJuego) )
			return;
		if( tecla == KEY_ESCAPE )
		{
			std::cout << "Presiono tecla: ESC\n";
			QuitarJugadorOp *quitarJugador = new QuitarJugadorOp( idJugador );
			Modelo::getInstance()->agregarOperacion( quitarJugador );
			break;
		}
		else
		{
			std::cout << "Presiono tecla: ";
			switch( tecla )
			{
			case KEY_ARRIBA: 
				std::cout<< "ARRIBA" << std::endl;
				break;
			case KEY_ABAJO: 
				std::cout<< "ABAJO" << std::endl;
				break;
			case KEY_DERECHA: 
				std::cout<< "DERECHA" << std::endl;
				break;
			case KEY_IZQUIERDA: 
				std::cout<< "IZQUIERDA" << std::endl;
				break;
			}
			Modelo::getInstance()->getJugador( idJugador )->SetKeyPressed( tecla );
		}
	}
}

int EscucharJugador::recibirMensaje()
{
	PktCabecera buffer;
	socket->recibir( (char*)(&buffer), sizeof(PktCabecera) );
	return (int)buffer.aux;
}
