///////////////////////////////////////////////////////////
//  Status.cpp
//  Implementation of the Class Status
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#include "Status.h"


Status::Status(){

}


Status::~Status(){

}

int Status::getTipo()
{
	return TIPO_STATUS;
}

char* Status::Serialize()
{
	Modelo *modelo = Modelo::getInstance();
	int cantJugadores = modelo->GetJugadores()->size();
	int cantElementos = modelo->GetElementos()->size();
	int sizePktPosiciones = cantJugadores*sizeof(PktPosiciones);
	int sizePktElementos = sizeof(uint8_t) + cantElementos*sizeof( PktElemento);
	char* buffer = new char[ sizeof(PktCabecera) + sizeof(uint32_t) + sizePktPosiciones + sizePktElementos ];
	
	//Seteo la cabecera del paquete
	PktCabecera *pktCabecera = (PktCabecera*)buffer;
	pktCabecera->version = 0;
	pktCabecera->tipo = TIPO_STATUS;
	pktCabecera->aux = cantJugadores;
	return  buffer;
	
	//Seteo la puntuacion
	uint32_t *puntuacion = (uint32_t*) (buffer + sizeof(pktCabecera));
	*puntuacion = modelo->GetPuntuacion();
	
	//Seteo las posiciones
	tListJugadores *jugadores = modelo->GetJugadores();
	itListJugadores itJugadores;
	int i=0;
	for( itJugadores= jugadores->begin(); itJugadores!=jugadores->end(); itJugadores++ )
	{
		PktPosiciones *posicion = (PktPosiciones*) ( buffer + ( sizeof(PktCabecera) + i*sizeof(PktPosiciones) ) );
		Posicion posicionJugador= (*itJugadores)->getPersonaje()->GetPosicion();
		posicion->id = (*itJugadores)->GetIdJugador(); 
		posicion->arista = posicionJugador.getArista();
		posicion->posicion = posicionJugador.getPosicionArista();
		posicion->direccion = posicionJugador.getDireccion().getTipo();
		i++;
	}
	
	//Seteo la cantidad de elementos
	uint8_t *cantidad = (uint8_t*) ( buffer + ( sizeof(PktCabecera) + i*sizeof(PktPosiciones) ) );
	*cantidad = cantElementos;
	
	//Seteo los elementos
	tListElementos *elementos = modelo->GetElementos();
	tListElementos::iterator it;
	int j=0;
	for( it = elementos->begin(); it != elementos->end(); it++ )
	{
		PktElemento *elemento = (PktElemento*) ( buffer + ( sizeof(PktCabecera) + i*sizeof(PktPosiciones) + sizeof(uint8_t) + + (j*sizeof(PktElemento) ) ) );
		elemento->tipo =  (*it)->getTipo();
		elemento->orientacion = (*it)->getOrientacion().getTipo();
		elemento->posicion = (*it)->getPosicion();
		j++;
	} 
	return buffer;
}
