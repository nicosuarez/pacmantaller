///////////////////////////////////////////////////////////
//  Init.cpp
//  Implementation of the Class Init
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#include "Init.h"


Init::Init( int rol)
{
	this->rol = rol;
}


Init::~Init()
{
}

int Init::getTipo()
{
	return TIPO_INIT;
}

tArco* getArco( tListaArco *arcos, Orientacion orientacion )
{
	tItArco it;
	for( it = arcos->begin(); it != arcos->end(); it++ )
		if( ( *(*it)->getElemento() ) == orientacion )
			return *it;
	return NULL;
}

char* Init::Serialize()
{
	Modelo *modelo = Modelo::getInstance();
	Mapa *mapa = modelo->GetMapa();
	std::list<tVertice*> *vertices = mapa->getGrafo()->getVertices();
	tListElementos *elementos = modelo->GetElementos();
	
	//Creo el espacio de memoria para el paquete a enviar
	int sizePktGrafo = ( (vertices->size()*2) + ((8-( vertices->size()*2 )%8)%8) )/8;
	int sizePktElementos = sizeof(uint16_t) + sizeof(PktElemento)*elementos->size();
	int size = sizeof(PktInit) + sizePktGrafo + sizePktElementos;
	char *buffer = new char[ size ];

	//Inicializo la cabecera y parte del cuerpo del paquete 
	PktInit *pktInit = (PktInit*)buffer;
	pktInit->version = 0;
	pktInit->tipo = TIPO_INIT;
	pktInit->rol = rol;	
	pktInit->padding = 0;
	pktInit->alto = mapa->getAlto();
	pktInit->ancho = mapa->getAncho();
	
	//Inicializo la parte del grafo del paquete
	tItVertice itActual, itInicial;
	itActual = vertices->begin();
	itInicial = itActual;
	int i=0;
	while( itActual != vertices->end() )
	{
		itInicial = itActual;
		//Recorro una fila y agrego al paquete los arcos Norte 
		for( int j=0; j< mapa->getAncho(); j++ )
		{
			uint8_t *byte = (uint8_t*)(buffer + sizeof(PktInit) + i/8);
			tListaArco *arcos = (*itActual)->getArcos();
			if( getArco( arcos, Norte) != NULL )
				*byte |= (1 <<  7-(i%8) );
			else 
				*byte &= ~(1 <<  7-(i%8) );
			itActual++;
			i++;
		}
		//Vuelvo a recorrer la misma fila y agrego al paquete los arcos Este
		itActual = itInicial;
		for( int j=0; j< mapa->getAncho(); j++ )
		{
			uint8_t *byte = (uint8_t*)(buffer + sizeof(PktInit) + i/8);
			tListaArco *arcos = (*itActual)->getArcos();
			if( getArco( arcos, Este) != NULL )
				*byte |= (1 <<  7-(i%8) );
			else 
				*byte &= ~(1 <<  7-(i%8) );
			itActual++;
			i++;
		}
	}
	
	//Lleno los bits que sobraron (padding) con cero
	for( int j= i%8; j<8; j++ )
	{
		uint8_t *byte = (uint8_t*)buffer + (sizeof(PktInit) + i/8);
		*byte &= ~(1 <<  7-(i%8) );
		i++;
	}
	//Seteo la cantidad de elementos
	uint16_t *cantElementos = (uint16_t *)( buffer + (sizeof(PktInit) + i/8) );
	*cantElementos = (uint16_t) ( modelo->GetElementos()->size() );

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
