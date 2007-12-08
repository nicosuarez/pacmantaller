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
bool AgregarJugadorOp::ejecutar()
{

	//Enviar mensaje init
	std::cout<<"Enviar mensaje init al jugador: "<<this->jugador->GetIdJugador()<<"\n";
	//Se le asigna un personaje al jugador
	this->asignarPersonaje();
	//Se le envia al cliente el paquete init
	this->enviarMsgInit();
	//Se espera 5 segundos y se envia el mensaje start agregando el jugador 
	//a la lista del modelo
	Play* play = new Play(this->jugador);
	play->run();
	StartJugador::getInstance()->agregarStart(play);
	
	return false;
}

void AgregarJugadorOp::enviarMsgInit()
{
	Socket *socket = jugador->GetSocket();
	int rol=jugador->getPersonaje()->GetRol();
	Init init(rol);
	char *buffer = init.Serialize();
	//socket->enviar( buffer, init.getSize());
	
	socket->enviar( buffer, sizeof(PktInit) );
	int delta = sizeof(PktInit);
	
	Mapa *mapa = Modelo::getInstance()->GetMapa();
	int cantAristas = mapa->getAlto()*mapa->getAncho()*2;
	int sizeGrafo = (  cantAristas + ( 8 - cantAristas%8 )%8  )/8;
	
	for(int i=0; i< sizeGrafo; i++ )
	{
		socket->enviar( buffer+delta, 1 );
		delta ++;
	}
	int cantElementos = *(buffer + delta);
	socket->enviar( (char*)(&cantElementos), sizeof(uint16_t) );
	delta += sizeof(uint16_t);
	
	int sizeElementos =cantElementos*sizeof(PktElemento);
	socket->enviar( buffer+delta, sizeElementos );
	delete[] buffer;
}

//Retorna el rol que se le asgino al jugador
void AgregarJugadorOp::asignarPersonaje()
{
	Personaje *personaje;
	Posicion posicion(1,2,0,4);//TODO Asignar la posicion correcta al personaje
	if( jugador->GetIdJugador() == PacMan::PACMAN_TYPE )
	{
		personaje = new PacMan();
		jugador->SetIdPersonaje(PacMan::PACMAN_TYPE);
	}
	else 
	{
		personaje = new Fantasma();
		jugador->SetIdPersonaje(Fantasma::FANTASMA_TYPE);
	}
	personaje->SetPosicion(posicion);
	jugador->SetPersonaje( personaje );
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
