#include "Modelo.h"

Modelo* Modelo:: pModelo = NULL;

Modelo::Modelo()
{
	puntuacion = 0;
	finalizoJuego = false;
	finalizoNivel = false;
	elementos = NULL;
	mapa = NULL;
}


Modelo* Modelo::getInstance () 
{
    if (pModelo == NULL)
    {  
    	pModelo = new Modelo(); 
    }
    return pModelo;
}

Modelo::~Modelo()
{
	eliminarPersonajes();
	if( elementos != NULL)
	{
		eliminarElementos();
		delete elementos;
	}
	if( mapa != NULL )
		delete mapa;
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

void Modelo::setMapa( Mapa *mapa )
{
	if( mapa != NULL)
		delete mapa;
	this->mapa = mapa;
}

void Modelo::setElementos( std::list<Elemento*> *elementos )
{
	this->elementos = elementos;
}

void Modelo::setEnviarMensaje( EnviarMensaje *enviarMensaje )
{
	this->enviarMensaje = enviarMensaje;
}

EnviarMensaje* Modelo::getEnviarMensaje()
{
	return enviarMensaje;
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

Mapa* Modelo::getMapa()
{
	return mapa;
}

std::list<Elemento*>* Modelo::getElementos()
{
	return elementos;
}

std::list<Personaje*>* Modelo::getPersonajes()
{
	return &personajes;
}

Personaje* Modelo::getPersonaje( int id )
{
	std::list<Personaje*>::iterator it;
	for( it = personajes.begin(); it != personajes.end(); it++ )
	{
		if( (*it)->GetRol() == id )
			return (*it);
	}
	return NULL;
}

void Modelo:: eliminarElementos()
{
	std::list<Elemento*>::iterator it;
	for( it = elementos->begin(); it != elementos->end(); it++ )
	{
		delete (*it);
	}
	elementos->clear();
}

void Modelo:: eliminarPersonajes()
{
	std::list<Personaje*>::iterator it;
	for( it=personajes.begin(); it!=personajes.end(); it++ )
	{
		delete(*it);
	}
	personajes.clear();
}
