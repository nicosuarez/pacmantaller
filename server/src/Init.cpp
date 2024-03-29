///////////////////////////////////////////////////////////
//  Init.cpp
//  Implementation of the Class Init
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#include "Init.h"

using namespace std;

Init::Init( int rol)
{
	this->rol = rol;
}


Init::~Init()
{
}

int getbit( int x, uint8_t byte )
{
	byte = byte << 7-x;
	byte = byte >> 7;
	return byte;
}

tArco* getArco( tListaArco *arcos, Orientacion orientacion )
{
	tItArco it;
	for( it = arcos->begin(); it != arcos->end(); it++ )
		if( ( (*it)->getElemento() ) == orientacion )
			return *it;
	return NULL;
}

char* Init::Serialize()
{
	Modelo *modelo = Modelo::getInstance();
	Mapa *mapa = modelo->GetMapa();
	tGrafo *grafo = mapa->getGrafo();
	tListElementos *elementos = modelo->GetElementos();

	//Creo el espacio en memoria para el paquete a enviar
	int cantAristas = mapa->getAlto()*mapa->getAncho()*2;
	int sizePadding = ( 8 - cantAristas%8 )%8;
	int sizePktGrafo = (cantAristas +  (	8-(cantAristas%8))%8 )/8;
	int sizePktElementos = sizeof(uint16_t) + sizeof(PktElemento)*(elementos->size() );
	sizePkt = sizeof(PktInit) + sizePktGrafo + sizePktElementos;
	char *buffer = new char[ sizePkt ];
	
	//Inicializo la cabecera y parte del cuerpo del paquete 
	PktInit *pktInit = (PktInit*)buffer;
	pktInit->version = 0;
	pktInit->tipo = Init::INIT_TYPE;
	pktInit->rol = rol;	
	pktInit->padding = 0;
	pktInit->alto = mapa->getAlto();
	pktInit->ancho = mapa->getAncho();
	
	//Inicializo la parte del grafo del paquete
	int i=0;
	int idVertice=0;
	int idInicial;
	while( idVertice < cantAristas/2 )
	{
		idInicial= idVertice;
		//Recorro una fila y agrego al paquete los arcos Norte 
		for( int j=0; j< mapa->getAncho(); j++ )
		{
			uint8_t *byte = (uint8_t*)(buffer + sizeof(PktInit) + i/8);
			//Obtengo el vertice
			tVertice* vertice = grafo->getVertice( idVertice );
			
			//Si el vertice existe busco el arco Norte
			if( vertice!= NULL )
			{
				//Si tiene arco Norte seteo el bit en 1
				if( getArco( vertice->getArcos(), Norte) != NULL )
					*byte |= (1 <<  7-(i%8) );
				//Si no tiene arco Norte seteo el bit en 0
				else 
					*byte &= ~(1 <<  7-(i%8) );
			}
			//Si el vertice no existe seteo el bit en 0
			else 
				*byte &= ~(1 <<  7-(i%8) );
			idVertice++;
			i++;
		}
		
		idVertice = idInicial;
		//Vuelvo a recorrer la misma fila y agrego al paquete los arcos Este
		for( int j=0; j< mapa->getAncho(); j++ )
		{
			uint8_t *byte = (uint8_t*)(buffer + sizeof(PktInit) + i/8);
			tVertice* vertice = grafo->getVertice( idVertice );
			//Si el vertice existe busco el arco Este
			if( vertice!= NULL )
			{
				//Si tiene arco Este seteo el bit en 1
				if( getArco( vertice->getArcos(), Este) != NULL )
					*byte |= (1 <<  7-(i%8) );
				//Si no tiene arco Este seteo el bit en 0
				else 
					*byte &= ~(1 <<  7-(i%8) );
			}
			//Si el vertice no existe seteo el bit en 0
			else 
				*byte &= ~(1 <<  7-(i%8) );
			idVertice++;
			i++;
		}
	}
	
	if( sizePadding > 0)
	{
		//Lleno los bits que sobraron (padding) con cero
		for( int j= i%8; j<8; j++ )
		{
			uint8_t *byte = (uint8_t*)buffer + (sizeof(PktInit) + i/8);
			*byte &= ~(1 <<  7-(i%8) );
			i++;
		}
	}
	//Seteo la cantidad de elementos
	uint16_t *cantElementos = (uint16_t *)( buffer + (sizeof(PktInit) + i/8) );
	*cantElementos = (uint16_t)( elementos->size() ) ;

	//Seteo los elementos
	tListElementos::iterator it;
	int j=0;
	for( it = elementos->begin(); it != elementos->end(); it++ )
	{
		PktElemento *elemento = (PktElemento*) ( buffer + (sizeof(PktInit) + i/8 + sizeof(uint16_t) + (j*sizeof(PktElemento)) ) );
		elemento->tipo =  (*it)->getTipo();
		elemento->orientacion = (*it)->getOrientacion();
		elemento->posicion = (*it)->getPosicion();
		j++;
	}
	return buffer;
}
