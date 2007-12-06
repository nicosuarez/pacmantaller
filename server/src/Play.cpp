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
	std::cout<<"Envia el mensaje start al jugador: "<< this->jugador->GetIdJugador()<<"\n";
	Start start(idJugador);
	char *buffer = start.Serialize();
	jugador->GetSocket()->enviar( buffer, start.getSize() );
	delete []buffer;
	//Status status( Modelo::getInstance()->GetElementos());
	//buffer = status.Serialize();
	//jugador->GetSocket()->enviar( buffer, status.getSize() );
	//delete []buffer;
	//Agregar el jugador al juego.
	std::cout<<"Agrega el jugador "<< this->jugador->GetIdJugador() << " al juego\n";
	Modelo::getInstance()->GetJugadores().push_back(this->jugador);
}
