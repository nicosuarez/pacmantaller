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
	std::cout<<"Enviar mensaje init al jugador: "<<this->jugador->GetIdJugador()<<"\n";
	//Se le asigna un personaje al jugador
	Personaje *personaje;
	int rol = 1;
	if( jugador->GetIdJugador() == 0 )
	{
		personaje = new PacMan;
		rol = 0;
	}
	else personaje = new Fantasma;
	jugador->SetPersonaje( personaje );
	//Se le envia al cliente el paquete init
	Init init(rol);
	char *buffer = init.Serialize();
	jugador->GetSocket()->enviar( buffer, (size_t)init.getSize() );
	//Se espera 5 segundos y se envia el mensaje start agregando el jugador 
	//a la lista del modelo
	Play* play = new Play(this->jugador);
	play->run();
	StartJugador::getInstance()->agregarStart(play);
	
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
