///////////////////////////////////////////////////////////
//  Status.cpp
//  Implementation of the Class Status
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#include "Status.h"


Status::Status()
{
	//Voy a agregar a la lista elementos, los elementos que fueron comidos por el
	//pacman, los que aparecieron y desaparecieron 
	Modelo *modelo = Modelo::getInstance();
	tListaElemento *elementosModelo = modelo->GetElementos();
	tListaElemento::iterator it;
	
	//Vertifico si las pastillas y los powerUp fueron comidos
	for( it = elementosModelo->begin(); it != elementosModelo->end(); it++ )
	{
		if( (*it)->getEstado() == FueComido )
		{
			elementos.push_back( *it );
			(*it)->setEstado( Eliminado );
		}
	}
	
	//Verifico si hay un powerUp nuevo o si alguno cambio de estado 
	elementosModelo = modelo->GetBonus();
	for( it = elementosModelo->begin(); it != elementosModelo->end(); it++ )
	{
		if( (*it)->getEstado() == FueComido )
		{
			elementos.push_back( *it );
			(*it)->setEstado( Eliminado );
		}
		if( (*it)->getEstado() == Aparece || (*it)->getEstado() == Desaparece )
			elementos.push_back( *it );
	}
}

Status::~Status()
{
}

char* Status::Serialize()
{
	Modelo *modelo = Modelo::getInstance();
	int cantJugadores = modelo->GetJugadores().size();
	int cantElementos = elementos.size();
	
	int sizePktPosiciones = sizeof(uint32_t) + cantJugadores*sizeof(PktPosiciones);
	int sizePktElementos = sizeof(uint8_t) + cantElementos*sizeof( PktElementoStatus); 
	sizePkt = sizeof(PktCabecera) + sizePktPosiciones + sizePktElementos; 
	char* buffer = new char[ sizePkt ];
	
	//Seteo la cabecera del paquete
	PktCabecera *pktCabecera = (PktCabecera*)buffer;
	pktCabecera->version = 0;
	pktCabecera->tipo = Status::STATUS_TYPE;
	pktCabecera->aux = cantJugadores-1;
	int delta = sizeof(PktCabecera);

	//Seteo la puntuacion
	uint32_t *puntuacion = (uint32_t*) ( buffer + delta );
	*puntuacion = htonl( modelo->GetPuntuacion() ); 
	delta += sizeof(uint32_t);

	
	//Seteo las posiciones
	tListJugadores jugadores = modelo->GetJugadores();
	itListJugadores itJugadores;
	
	for( itJugadores= jugadores.begin(); itJugadores!=jugadores.end(); itJugadores++ )
	{
		PktPosiciones *posicion = (PktPosiciones*) ( buffer + delta );
		Posicion *posicionJugador = (*itJugadores)->getPersonaje()->GetPosicion();
		posicion->id = (*itJugadores)->GetIdJugador(); 
		posicion->arista = posicionJugador->getArista();
		posicion->posicion = posicionJugador->getPosicionArista();
		posicion->direccion = posicionJugador->getDireccion();
		delta += sizeof(PktPosiciones);
	}	
	//Seteo la cantidad de elementos
	uint8_t *cantidad = (uint8_t*) ( buffer + delta );
	*cantidad = cantElementos;
	delta += sizeof( uint8_t );
	
	//Seteo los elementos
	tListElementos::iterator it;
	for( it = elementos.begin(); it != elementos.end(); it++ )
	{
		PktElementoStatus *elemento = (PktElementoStatus*) ( buffer + delta  );
		elemento->tipo =  (int)(*it)->getTipo();
		elemento->orientacion = (*it)->getOrientacion();
		elemento->estado = (*it)->getEstado();
		elemento->posicion = (*it)->getPosicion();
		delta += sizeof(PktElementoStatus);
	} 
	return buffer;
}
