///////////////////////////////////////////////////////////
//  EscucharJugador.cpp
//  Implementation of the Class EscucharJugador
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#include "EscucharJugador.h"


EscucharJugador::EscucharJugador(Socket* sk_jugador){
	this->sk_jugador=sk_jugador;
}

EscucharJugador::~EscucharJugador(){

}

/**
 * Hilo que se encarga de escuchar los mensajes que el jugador recibe del servidor
 */
void EscucharJugador::main(){
	this->recibirMensaje();
}


void EscucharJugador::recibirMensaje(){
	std::string msg="";
	this->sk_jugador->recibir(msg,1000);
}
