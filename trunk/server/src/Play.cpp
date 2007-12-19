#include "Play.h"

Play::Play(Jugador* jugador)
{
	this->jugador=jugador;
}

void Play::main()
{
	//Esperar 5 segundos para que el cliente pueda mostrar el mapa
	sleep(1000);
	int idJugador = jugador->GetIdJugador();
	//Enviar mensaje start
	Start start(idJugador);
	char* buffer = start.Serialize();
	jugador->GetSocket()->enviar( buffer, start.getSize() );
	delete []buffer;
	
	//Si no esta jugando, agregar el jugador al juego.
	if(!Modelo::getInstance()->estaJugando(jugador))
	{
		Modelo::getInstance()->agregarJugador( jugador );
	}
	
	Modelo::getInstance()->getEsperarAgregarJugadores().activar();
}
