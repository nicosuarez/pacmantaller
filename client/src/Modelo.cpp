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
	{
		this->m_mapa.lock();
		delete mapa;
		this->m_mapa.unlock();
	}
		
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
	this->m_mapa.lock();
	if( this->mapa != NULL)
		delete mapa;
	this->mapa = mapa;
	this->m_mapa.unlock();
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
			std::cout<<"Buscar bonus...\n";
			tListBonus::iterator it;
			for( it = bonus.begin(); it != bonus.end(); it++ )
			{
				if( (*it)->getPosicion() == posicion )
				{
					std::cout<<"encontro bonus...\n";
					return (*it);
				}
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
	this->m_personajes.lock();
	for( it=personajes.begin(); it!=personajes.end(); it++ )
	{
		delete(*it);
	}
	personajes.clear();
	this->m_personajes.unlock();
}

void Modelo:: eliminarPastillas()
{
	tListPastilla::iterator it;
	this->m_pastillas.lock();
	for( it = pastillas.begin(); it != pastillas.end(); it++ )
	{
		delete(*it);
	}
	pastillas.clear();
	this->m_pastillas.unlock();
}

void Modelo:: eliminarBonus()
{
	tListBonus::iterator it;
	this->m_bonus.lock();
	for( it= bonus.begin(); it != bonus.end(); it++ )
	{
		delete(*it);
	}
	bonus.clear();
	this->m_bonus.unlock();
}

void Modelo:: eliminarPowers()
{
	tListPower::iterator it;
	this->m_powers.lock();
	for( it= powers.begin(); it != powers.end(); it++ )
	{
		delete(*it);
	}
	powers.clear();
	this->m_powers.lock();
}


Camara& Modelo::getCamara() {
	return camara;
}

Mutex& Modelo::getMutexPastillas()
{
	return this->m_pastillas;
}

Mutex& Modelo::getMutexBonus()
{
	return this->m_bonus;
}

Mutex& Modelo::getMutexPowers()
{
	return this->m_powers;
}

Mutex& Modelo::getMutexPersonajes()
{
	return this->m_personajes;
}

Mutex& Modelo::getMutexMapa()
{
	return this->m_mapa;
}

//void Modelo::quitarBonus( int idPosicion )
//{
//	tListBonus::iterator it;
//	m_bonus.lock();
//	for( it = bonus.begin(); it != bonus.end(); it++ )
//	{
//		if( (*it)->getPosicion() == idPosicion )
//		{
//			delete (*it);
//			bonus.erase( it );
//			break;
//		}
//	}
//	m_bonus.unlock();
//}


