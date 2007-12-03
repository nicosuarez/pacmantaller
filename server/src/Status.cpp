///////////////////////////////////////////////////////////
//  Status.cpp
//  Implementation of the Class Status
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#include "Status.h"


Status::Status( tListaElemento *elementos )
{	
	this->elementos = elementos;
}


Status::~Status(){

}

char* Status::Serialize()
{
	Modelo *modelo = Modelo::getInstance();
	int cantJugadores = modelo->GetJugadores().size();
	int cantElementos = elementos->size();
	
	int sizePktPosiciones = sizeof(uint32_t) + cantJugadores*sizeof(PktPosiciones);
	int sizePktElementos = sizeof(uint8_t) + cantElementos*sizeof( PktElementoStatus); 
	sizePkt = sizeof(PktCabecera) + sizePktPosiciones + sizePktElementos; 
	char* buffer = new char[ sizePkt ];
	
	//Seteo la cabecera del paquete
	PktCabecera *pktCabecera = (PktCabecera*)buffer;
	pktCabecera->version = 0;
	pktCabecera->tipo = Status::STATUS_TYPE;
	pktCabecera->aux = cantJugadores;
	int delta = sizeof(PktCabecera);

	//Seteo la puntuacion
	uint32_t *puntuacion = (uint32_t*) ( buffer + delta );
	*puntuacion = modelo->GetPuntuacion(); 
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
	for( it = elementos->begin(); it != elementos->end(); it++ )
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
