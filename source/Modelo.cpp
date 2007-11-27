///////////////////////////////////////////////////////////
//  Modelo.cpp
//  Implementation of the Class Modelo
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#include "Modelo.h"

Modelo* Modelo::pModelo = NULL;

Modelo* Modelo::getInstance () 
{
    if (pModelo == NULL)
    {  
    	pModelo = new Modelo(); 
    }
    return pModelo;
}
/*----------------------------------------------------------------------------*/
/**
 * Se setea una unica instancia del modelo.
 */
void Modelo::setInstance(pBool finalizoJuego,pBool cerroServidor)
{
	if (pModelo == NULL)
    {  
    	pModelo = new Modelo(finalizoJuego,cerroServidor);
    }
}
/*----------------------------------------------------------------------------*/
Modelo::Modelo(pBool finalizoJuego,pBool cerroServidor){
	this->finalizoJuego=finalizoJuego;
	this->cerroServidor=cerroServidor;
}
/*----------------------------------------------------------------------------*/
Modelo::Modelo(){
	this->finalizoJuego=NULL;
	this->cerroServidor=NULL;
}
/*----------------------------------------------------------------------------*/
Modelo::~Modelo(){

}
/*----------------------------------------------------------------------------*/
/**
 * Coloca la operacion en la cola.
 */
void Modelo::agregarOperacion(Operacion* operacion){

}
/*----------------------------------------------------------------------------*/
/**
 * Lista de elementos del mapa.
 */
tListElementos* Modelo::GetElementos(){

	return &elementos;
}
/*----------------------------------------------------------------------------*/
/**
 * Nivel que se esta jugando actualmente.
 */
Mapa* Modelo::GetMapa(){

	return mapa;
}
/*----------------------------------------------------------------------------*/
/**
 * Lista de jugadores puede ser PacMan o Fantasma
 */
tListJugadores* Modelo::GetJugadores(){
	return &jugadores;
}
/*----------------------------------------------------------------------------*/
int Modelo::GetPuntuacion()const
{
	return puntuacion;
}

/**
 * Ejecucion del hilo.
 */
void Modelo::main(){
	//Obtener el mundo.
	//this->mundo = XmlParser::getMundo(Config::getInstance()->GetMundoXmlPath());
	
	while(!this->seFinalizoElJuego())
	{
		//Obtener el mapa del nivel.
		//this->mapa = XmlParser::getMapa(Mundo->nivel->mapaPath);
		while(!this->seFinalizoElNivel())
		{
			this->ejecutarOperaciones();
			//Correr ActualizarEstado...
		}
	}
	
}
/*----------------------------------------------------------------------------*/
/**
 * Desacola una operacion de la cola y la ejecuta.
 */
void Modelo::ejecutarOperaciones(){
	
}
/*----------------------------------------------------------------------------*/
/**
 * Notifica que los jugadores deben actualizar el estado
 */
void Modelo::notify(){

}
/*----------------------------------------------------------------------------*/
/**
 * Lista de elementos del mapa.
 */
void Modelo::SetElementos(tListElementos elementos){

	this->elementos = elementos;
}
/*----------------------------------------------------------------------------*/
/**
 * Nivel que se esta jugando actualmente.
 */
void Modelo::SetMapa(Mapa *mapa)
{
	this->mapa = mapa;
}
/*----------------------------------------------------------------------------*/
/**
 * Lista de jugadores puede ser PacMan o Fantasma
 */
void Modelo::SetJugadores(tListJugadores jugadores){

	this->jugadores = jugadores;
}
