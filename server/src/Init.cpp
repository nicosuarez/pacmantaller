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

tArco* getArco( tListaArco *arcos, Orientacion orientacion )
{
	tItArco it;
	for( it = arcos->begin(); it != arcos->end(); it++ )
		if( ( (*it)->getElemento() ) == orientacion )
			return *it;
	return NULL;
}


int getbit( int x, uint8_t byte )
{
	byte = byte << 7-x;
	byte = byte >> 7;
	return byte;
}

void imprimir( char* pkt)
{
	PktInit *pktInit = (PktInit*) pkt;
	cout << "Version: " << (int)pktInit->version << endl;
	cout << "Tipo: " << (int)pktInit->tipo << endl;
	cout << "Rol: " << (int)pktInit->rol << endl;
	cout << "Ancho: " << (int)pktInit->ancho << endl;
	cout << "Alto: " << (int)pktInit->alto << endl;
	int tamanio = ((int)pktInit->ancho)*((int)pktInit->alto)*2;
	int i;
	for(i=0; i<tamanio; i++)
	{
		uint8_t *byte = (uint8_t*)(pkt + sizeof(PktInit) + i/8);
		cout << getbit( 7 - (i%8), *byte );
	}
	cout<< endl;
	//salteo los bits del padding
	i += 8- i%8;
	uint16_t *cantElementos = (uint16_t*) (pkt + (sizeof(PktInit) + i/8 ));
	cout << "Cant Elementos: " << (int)(*cantElementos) << endl;
	for(int j=0; j<(int)(*cantElementos); j++ )
	{
		PktElemento *elemento = (PktElemento*) (pkt + (sizeof(PktInit) + i/8 + 2 + j*sizeof(PktElemento)));
		cout << "Tipo: " << (int)elemento->tipo << endl;
		cout << "Orientacion: " << (int)elemento->orientacion<< endl;
		cout << "Posicion: " << (int)elemento->posicion<< endl;
	}
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
	imprimir(buffer);
	return buffer;
}
