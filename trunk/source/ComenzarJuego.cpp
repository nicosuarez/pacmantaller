///////////////////////////////////////////////////////////
//  CerrarServidor.cpp
//  Implementation of the Class CerrarServidor
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "ComenzarJuego.h"


ComenzarJuego::ComenzarJuego(Socket* sk, pBool finalizoJuego,
		                     pBool cerrarServidor){
	this->skServer=sk;
	this->finalizoJuego=finalizoJuego;
	this->cerrarServidor=cerrarServidor;
}
/*----------------------------------------------------------------------------*/
ComenzarJuego::~ComenzarJuego(){

}
/*----------------------------------------------------------------------------*/
/**
 * Se ejecuta el hilo principal del juego el del modelo.
 */
void ComenzarJuego::main(){

	//Se empieza aceptar jugadores a traves del socket del servidor, hasta que
	//finalice el juego.
	AceptarJugador aceptarJugador(skServer,finalizoJuego);
	aceptarJugador.run();
	
	//Se instancia el modelo. Singleton
	//finalizoJuego,cerrarServidor son flags de estado.
	Modelo::setInstance(finalizoJuego,cerrarServidor);
	Modelo::getInstance()->run();
}
