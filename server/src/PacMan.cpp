///////////////////////////////////////////////////////////
//  PacMan.cpp
//  Implementation of the Class PacMan
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#include "PacMan.h"



PacMan::PacMan(){
	this->isPowerUp=false;
	this->velocidad=velocidadInicial;
	this->puntaje=0;
}

PacMan::PacMan(Posicion& posicion):Personaje(posicion){
	this->isPowerUp=false;
	this->velocidad=velocidadInicial;
	this->puntaje=0;
}

PacMan::~PacMan(){

}

/**
 * Identificador del rol de personaje
 */
int PacMan::GetRol()const{

	return PacMan::PACMAN_TYPE;
}

/**
 * El radio da una idea del volumen del personaje, y usa para detectar colisiones.
 */
double PacMan::getRadio()const
{
	return PacMan::radio;
}

/**
 * Velocidad del personaje
 */
int PacMan::GetVelocidad(){

	return this->velocidad;
}

/**
 * Determina si el pacman se encuentra en el estado powerUp
 */
bool PacMan::IsPowerUp(){

	if(isPowerUp)
	{
		if(mantenerEstado.getTime()<tiempoPowerUp)
		{
			return true;
		}
		else
		{
			mantenerEstado.initial();
			isPowerUp=false;
			Modelo::getInstance()->restoreDefaultSpeed();
			return false;
		}
	}
	return false;
}


/**
 * Determina si el pacman se encuentra en el estado powerUp
 */
void PacMan::SetPowerUp(){
	mantenerEstado.initial();
	isPowerUp=true;
	Modelo::getInstance()->intercambiarVelocidades();
}

bool PacMan::operator==( int tipo )const
{
	return tipo == PACMAN_TYPE;
}

void PacMan::comer()
{
	Modelo* modelo = Modelo::getInstance();
	Posicion* posicion= this->GetPosicion();
	if(this->chocoConPared())
	{
		tVertice* vDest = ActualizarJuego::getVeticeDestino(posicion);
		//Come la comida del vertice destino
		modelo->comerElementoDelVertice(vDest);
	}
	else
	{
		//Come la comida del vertice origen
		Mapa* mapa = Modelo::getInstance()->GetMapa();
		tVertice* vOrig = mapa->getGrafo()->getVertice(posicion->getVertice());
		modelo->comerElementoDelVertice(vOrig);
	}
	
}

