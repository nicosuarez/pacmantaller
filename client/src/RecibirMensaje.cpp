#include "RecibirMensaje.h"

RecibirMensaje::RecibirMensaje( Socket *socket ):socket(socket)
{
}

RecibirMensaje::~RecibirMensaje()
{
}

void RecibirMensaje:: main()
{
	this->recibirMensaje();
}

void RecibirMensaje::recibirMensaje()
{
	Modelo *modelo = Modelo::getInstance();
	char buffer[sizeof(PktCabecera)];
	//Mientras no haya finalizado el juego sigue recibiendo paquetes
	while( !modelo->getFinalizoJuego() )
	{
		socket->recibir( buffer, sizeof(PktCabecera) );
		PktCabecera *cabecera = (PktCabecera*)buffer;
		switch( (int) cabecera->tipo )
		{
			case Mensaje::INIT_TYPE: 
				recibirInit( cabecera );
				break;
				
			case Mensaje::START_TYPE:
				//Recibo el id
				char id[sizeof( uint16_t)];
				socket->recibir( id, sizeof(uint16_t) );
				modelo->setid( (int)(*id) );
				break;
				
			case Mensaje::STATUS_TYPE:
				recibirStatus( cabecera );
				break;
				
			case Mensaje::STOP_TYPE:
				//recibo la puntuacion del pacman
				char puntuacion[sizeof(uint32_t)];
				socket->recibir( puntuacion, sizeof(uint32_t) );
				//FALTA VER QUE SE HACE CON LA "RAZON" DE PORQUE FINALIZO EL NIVEL
				modelo->setFinalizoNivel( true );
				modelo->setPuntuacion( (int)(*puntuacion) );
				break;
				
			case Mensaje::QUIT_TYPE:
				modelo->setFinalizoJuego( true );
				break;
				
			default: continue;
		} 
	}
}

void agregarElemento( std::list<Elemento*> *elementos, PktElemento *pktElemento )
{
	int tipo = (int)pktElemento->tipo;
	Orientacion orientacion = (Orientacion)pktElemento->orientacion;
	int posicion = (int)pktElemento->posicion;
	switch( tipo )
	{
		case (int)tSalidaPacman:
			Modelo::getInstance()->getElementos()->push_back(new SalidaPacMan(posicion, orientacion));
			break;
		case (int)tCasaFantasmas:
			Modelo::getInstance()->getElementos()->push_back( new CasaFantasmas( posicion, orientacion) );
			break;
		case (int)tPowerup:
			Modelo::getInstance()->getElementos()->push_back( new PowerUp( posicion, orientacion) );
			break;
		case (int)tBonus:
			Modelo::getInstance()->getElementos()->push_back( new Bonus( posicion, orientacion) );
			break;			
		case (int)tPastilla:
			Modelo::getInstance()->getElementos()->push_back( new Pastilla( posicion, orientacion) );
			break;
		default: return;
	}
}

void RecibirMensaje::recibirElementos( int cantElementos )
{
	int tamanio = cantElementos*sizeof(PktElemento);
	char buffer[tamanio];
	socket->recibir( buffer, tamanio );
	std::list<Elemento*> *elementos = new std::list<Elemento*>;
	int delta = 0;
	for( int i=0; i<cantElementos; i++ )
	{
		PktElemento *pktElemento = (PktElemento*) (buffer + delta);
		agregarElemento( elementos, pktElemento );
		delta += sizeof(PktElemento);
	}
}

int getbit( int x, uint8_t byte )
{
	byte = byte << 7-x;
	byte = byte >> 7;
	return byte;
}

void RecibirMensaje::recibirMapa( int ancho, int alto )
{
	//Calculo la cantidad de bytes que hay que recibir
	int tamanio = ( (ancho*alto*2)  + ( (8-(ancho*alto*2)%8) %8 ) )/8;
	char buffer[ tamanio ];
	
	//Recibo los bytes con la informacion del mapa
	socket->recibir( buffer, tamanio );
	
	//Aloco memoria para las matrices que representan las paredes verticales y horizontales del mapa
	int **ph = new int*[alto];
	int **pv = new int*[alto];
	for( int i=0; i<alto; i++ )
	{
		ph[i] = new int[ancho];
		pv[i] = new int[ancho];
	}
	int contador = 0;
	int numFila = 0;
	while( contador < (ancho*alto*2) )
	{
		for( int i=0; i< ancho; i++)
		{
			uint8_t *byte = (uint8_t*)(buffer + contador/8);
			if( getbit( 7 - (i%8), *byte ) == 0 )
				ph[numFila][i] = 1;
			else 
				ph[numFila][i] = 0;
			contador++;
		}
		for( int i=0; i< ancho; i++ )
		{
			uint8_t *byte = (uint8_t*)(buffer + contador/8);
			if( getbit( 7 - (i%8), *byte ) == 0 )
				pv[numFila][i] = 1;
			else 
				pv[numFila][i] = 0;
			contador++;
		}
		numFila++;
	}
	Modelo::getInstance()->setMapa( new Mapa(ph, pv, ancho, alto ) );
}

void RecibirMensaje::recibirInit( PktCabecera *cabecera )
{
	//Recibo el ancho y alto del mapa
	char buffer[sizeof(uint16_t)];
	socket->recibir( buffer, sizeof(uint16_t) );
	int ancho = (uint8_t)(*buffer);
	int alto = (uint8_t)(*(buffer + sizeof(uint8_t) ) );
	
	//Recibo el mapa
	recibirMapa( ancho, alto );
	
	//Recibo la cantidad de elementos que hay en el mapa
	char ptrCantElementos[sizeof(uint16_t)];
	socket->recibir( ptrCantElementos, sizeof(uint16_t) );
	int cantElementos = (int)(*ptrCantElementos);
	
	//Recibo los elementos del mapa
	recibirElementos( cantElementos );
}

void RecibirMensaje::recibirElementosStatus( int cantElementos )
{
	int tamanio = cantElementos*sizeof(PktElementoStatus);
	char elementos[ tamanio ];
	socket->recibir( elementos, tamanio );
	std::list<Elemento*> *listElementos = new std::list<Elemento*>;
	int delta = 0;
	for( int i=0; i< cantElementos; i++ )
	{
		PktElementoStatus *elemento = (PktElementoStatus*)(elementos + delta);
		if( elemento->estado == Aparece )
		{
			PktElemento pktElemento;
			pktElemento.tipo = elemento->tipo;
			pktElemento.orientacion = elemento->orientacion;
			pktElemento.posicion = elemento->posicion;
			agregarElemento( listElementos, &pktElemento );
		}	
		delta += sizeof(PktElementoStatus);
	}
	Modelo *modelo = Modelo::getInstance();
	modelo->eliminarElementos();
	Modelo::getInstance()->setElementos( listElementos );
}

void RecibirMensaje::recibirPosiciones( int cantJugadores )
{
	int tamanio = cantJugadores*sizeof(PktPosiciones);
	char posiciones[ tamanio ];
	socket->recibir( posiciones, tamanio );
	int delta = 0;
	for( int i=0; i<cantJugadores; i++ )
	{
		PktPosiciones *pktPosicion = (PktPosiciones*)(posiciones + delta);
		int idJugador = (int)pktPosicion->id;
		int idArista = (int)pktPosicion->arista;
		int posicionArista = (int)pktPosicion->posicion;
		int direccion = (int)pktPosicion->direccion;
		Posicion posicion( idArista, posicionArista, direccion );
		Modelo *modelo = Modelo::getInstance();
		Personaje *personaje = modelo->getPersonaje( idJugador);
		//Si el jugador no existe, lo agrega. 
		if( personaje == NULL )
		{
			if( idJugador == 0 )
				personaje = new PacMan;
			else
				personaje = new Fantasma;
		}
		//Actualiza la posicion
		personaje->SetPosicion( posicion );
		delta += sizeof(PktPosiciones);
	}
}

void RecibirMensaje::recibirStatus( PktCabecera *cabecera )
{
	Modelo *modelo = Modelo::getInstance();
	//Recibo la puntuacion
	char puntuacion[sizeof(uint32_t)];
	socket->recibir( puntuacion, sizeof(uint32_t) );
	modelo->setPuntuacion( (int)(*puntuacion) );
	
	//Recibo las posiciones de los jugadores
	recibirPosiciones( (int)cabecera->aux );
	
	//Recibo la cantidad de elementos
	char buffer[sizeof(uint8_t)];
	socket->recibir( buffer, sizeof(uint8_t) );
	
	//Recibo los elementos
	recibirElementos( (int)(*buffer) );
	
}
