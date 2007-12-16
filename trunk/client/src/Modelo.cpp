#include "Modelo.h"

Modelo* Modelo:: pModelo = NULL;

Modelo::Modelo()
{
	puntuacion = 0;
	finalizoJuego = false;
	finalizoNivel = false;
	salidaPacMan = NULL;
	casaFantasmas = NULL;
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
	eliminarPastillas();
	eliminarBonus();
	eliminarPowers();
	if( mapa != NULL )
		delete mapa;
	if( salidaPacMan != NULL )
		delete salidaPacMan;
	if( casaFantasmas != NULL )
		delete casaFantasmas;
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
	if( this->mapa != NULL)
		delete mapa;
	this->mapa = mapa;
}

void Modelo::setCasaFantasmas( CasaFantasmas* casaFantasmas )
{
	
	this->casaFantasmas = casaFantasmas;
}

void Modelo::setSalidaPacMan( SalidaPacMan* salidaPacMan )
{
	cout<<"no debe ser null si seteo la salida pacman"<<endl;
	this->salidaPacMan = salidaPacMan;
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

Evento& Modelo::getRecibiMensajeInitEvent()
{
	return this->recibiMensajeInitEvent;
}

tListPastilla& Modelo::getPastillas()
{
	return pastillas;
}

tListBonus& Modelo::getBonus()
{
	return bonus;
}

tListPower& Modelo::getPowers()
{
	return powers;
}

tListPersonaje& Modelo::getPersonajes()
{
	return personajes;
}

Personaje* Modelo::getPersonaje( int id )
{
	tListPersonaje::iterator it;
	for( it = personajes.begin(); it != personajes.end(); it++ )
	{
		if( (*it)->GetRol() == id )
			return (*it);
	}
	return NULL;
}

Elemento* Modelo:: getElemento( tipoElemento tipo, int posicion )
{
	switch( (int)tipo )
	{
		case tPastilla:
		{
			tListPastilla::iterator it;
			for( it = pastillas.begin(); it != pastillas.end(); it++ )
			{
				if( (*it)->getPosicion() == posicion )
					return (*it);
			}
			break;
		}
		case tBonus:
		{
			tListBonus::iterator it;
			for( it = bonus.begin(); it != bonus.end(); it++ )
			{
				if( (*it)->getPosicion() == posicion )
					return (*it);
			}
			break;
		}
		case tPowerup:
		{
			tListPower::iterator it;
			for( it = powers.begin(); it != powers.end(); it++ )
			{
				if( (*it)->getPosicion() == posicion )
					return (*it);
			}
			break;
		}
	}
	return NULL;
}

CasaFantasmas* Modelo::getCasaFantasmas()
{
	return casaFantasmas;
}

SalidaPacMan* Modelo::getSalidaPacMan()
{
	return salidaPacMan;
}

void Modelo:: eliminarPersonajes()
{
	tListPersonaje::iterator it;
	for( it=personajes.begin(); it!=personajes.end(); it++ )
	{
		delete(*it);
	}
	personajes.clear();
}

void Modelo:: eliminarPastillas()
{
	tListPastilla::iterator it;
	for( it = pastillas.begin(); it != pastillas.end(); it++ )
	{
		delete(*it);
	}
	pastillas.clear();
}

void Modelo:: eliminarBonus()
{
	tListBonus::iterator it;
	for( it= bonus.begin(); it != bonus.end(); it++ )
	{
		delete(*it);
	}
	bonus.clear();
}

void Modelo:: eliminarPowers()
{
	tListPower::iterator it;
	for( it= powers.begin(); it != powers.end(); it++ )
	{
		delete(*it);
	}
	powers.clear();
}
