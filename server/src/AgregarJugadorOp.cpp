///////////////////////////////////////////////////////////
//  AgregarJugadorOp.cpp
//  Implementation of the Class AgregarJugadorOp
//  Created on:      21-Nov-2007 23:40:17
///////////////////////////////////////////////////////////

#include "AgregarJugadorOp.h"


AgregarJugadorOp::AgregarJugadorOp(Jugador* jugador){
	this->jugador=jugador;
}

/**
 * Valida y aplica la operacion* retorna TRUE(exito),FALSE(error)
 */
bool AgregarJugadorOp::ejecutar(Modelo* modelo){

	//Enviar mensaje init
	std::cout<<"Enviar mensaje init\n";
	
	//Se espera 5 segundos y se envia el mensaje start agregando el jugador 
	//a la lista del modelo
	Play play(this->jugador);
	play.run();
	
	return false;
}


/**
 * Metodo que encapsula la logica de la operacion.
 */
void AgregarJugadorOp::internalProcess(){

}


/**
 * Metodo que valida la operacion. TRUE(exito),
 * * FALSE(error)
 */
bool AgregarJugadorOp::validarOperacion(){

	return false;
}
