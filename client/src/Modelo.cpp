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

Modelo::Modelo()
{
	puntuacion = 0;
	finalizoJuego = false;
	finalizoNivel = false;
}

Modelo::~Modelo()
{
}

void Modelo::setid( int newid)
{
	this->id = newid;
}

void Modelo::setPuntuacion( int newPuntuacion )
{
	this->puntuacion = newPuntuacion;
}

void Modelo::setFinalizoJuego( bool finalizo )
{
	this->finalizoJuego = finalizo;
}

void Modelo::setFinalizoNivel( bool finalizo )
{
	this->finalizoNivel = finalizo;
}

void Modelo::setMatrices( int **ph, int **pv )
{
	this->ph = ph;
	this->pv = pv;
}

void Modelo::setElementos( std::list<Elemento*> *elementos )
{
	this->elementos = elementos; 
}

int Modelo::getid()const
{
	return this->id;
}

int Modelo::getPuntuacion()const
{
	return this->puntuacion;
}

bool Modelo::getFinalizoJuego()const
{
	return this->finalizoJuego;
}

bool Modelo::getFinalizoNivel()const
{
	return this->finalizoNivel;
}

int** Modelo::getph()const
{
	return this->ph;
}

int** Modelo::getpv()const
{
	return this->pv;
}

std::list<Elemento*>* Modelo::getElementos()const
{
	return elementos;
}
