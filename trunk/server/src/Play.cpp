#include "Play.h"

Play::Play(Jugador* jugador)
{
	this->jugador=jugador;
}

void Play::main()
{
	//Esperar 5 segundos para que el cliente pueda mostrar el mapa
	std::cout<<"Esperar que el jugador " << this->jugador->GetIdJugador()<<" muestre el mapa\n";
	sleep(1000);
	int idJugador = jugador->GetIdJugador();
	//Enviar mensaje start
	std::cout<<"Envia el mensaje start al jugador: "<< idJugador<<"\n";
	Start start(idJugador);
	char* buffer = start.Serialize();
	jugador->GetSocket()->enviar( buffer, start.getSize() );
	delete []buffer;
	
	//Si no esta jugando, agregar el jugador al juego.
	if(!Modelo::getInstance()->estaJugando(jugador))
	{
		std::cout<<"Agrega el jugador "<< idJugador << " al juego\n";
		Modelo::getInstance()->agregarJugador( jugador );
	}
	
	Modelo::getInstance()->getEsperarAgregarJugadores().activar();
	Status *status = new Status( Modelo::getInstance()->GetElementos());
	Modelo::getInstance()->getDispatcher()->enviarMensaje( status, idJugador );
}
