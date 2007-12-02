///////////////////////////////////////////////////////////
//  Servidor.cpp
//  Implementation of the Class Servidor
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#include "Servidor.h"
#include <sstream>

Servidor::Servidor(int maxcon){
	  this->skServer = new Socket(Config::getInstance()->GetPort(),maxcon);
	  this->finalizoJuego = false;
	  this->cerrarServidor=false;
}
/*----------------------------------------------------------------------------*/
Servidor::~Servidor(){
	delete skServer;
	delete Config::getInstance();
	delete ConnectionManager::getInstance();
	delete Modelo::getInstance();
}
/*----------------------------------------------------------------------------*/
int Servidor::ejecutar(){
	
	//Se pone a monitorear la entrada por teclado para poder cerrar el server.
	MonitorearEntrada monitor(&cerrarServidor);
	monitor.run();	
	while(!this->cerrarServidor)
	{
		this->finalizoJuego=false;
		//Comienza el juego.
		this->comenzarJuego();
	}
	monitor.join();
	return 0;
}
/*----------------------------------------------------------------------------*/
/**
 * Se ejecuta el hilo principal del juego el del modelo.
 */
void Servidor::comenzarJuego(){

	//Se empieza aceptar jugadores a traves del socket del servidor, hasta que
	//finalice el juego.
	AceptarJugador aceptarJugador(skServer,&finalizoJuego);
	aceptarJugador.run();
	
	//Se instancia el modelo. Singleton
	//finalizoJuego,cerrarServidor son flags de estado.
	Modelo::setInstance(&finalizoJuego,&cerrarServidor);
	
	//El connectionManager le setea al modelo la lista de jugadores conectados
	tListJugadores jugadores = ConnectionManager::getInstance()->GetPool().getJugadoresList();
	Modelo::getInstance()->SetJugadores(jugadores);
	
	//Comienza el juego...
	Modelo::getInstance()->run();
	
	//Espera que finalice...
	Modelo::getInstance()->join();
	
	//Deja de aceptar jugadores
	this->terminarDeAceptarClientes();
	aceptarJugador.join();
}
/*----------------------------------------------------------------------------*/
void Servidor::terminarDeAceptarClientes()
{
	Socket socket("127.0.0.1",Config::getInstance()->GetPort());
}
