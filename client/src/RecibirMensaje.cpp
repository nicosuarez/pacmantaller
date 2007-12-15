#include "RecibirMensaje.h"

#define LONGVERTICE 2
#define ALTURAITEMS 0.5

using namespace std;

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
	char *buffer = new char[sizeof(PktCabecera)];
	//Mientras no haya finalizado el juego sigue recibiendo paquetes
	while( !modelo->getFinalizoJuego() )
	{
		socket->recibir( buffer, sizeof(PktCabecera) );
		std::cout << "Recibi Paquete ";
		PktCabecera *cabecera = (PktCabecera*)buffer;
		switch( (int) cabecera->tipo )
		{
			case Mensaje::INIT_TYPE:
			{
				std::cout<< "Init\n";
				recibirInit( cabecera );
				//Comienza el cliente a dibijar el mapa...
				modelo->getRecibiMensajeInitEvent().activar();
				break;
			}
			case Mensaje::START_TYPE:
			{
				std::cout<< "Start\n";
				//Recibo el id
				uint16_t id;
				socket->recibir( (char*)(&id), sizeof(uint16_t) );
				id = ntohs(id);
				std::cout << "ID: " << (int)id << std::endl;
				modelo->setid( (int)(id) );
				break;
			}	
			case Mensaje::STATUS_TYPE:
			{
				std::cout<< "Status\n";
				recibirStatus( cabecera );
				break;
			}	
			case Mensaje::STOP_TYPE:
			{
				std::cout<< "Stop\n";
				//recibo la puntuacion del pacman
				char puntuacion[sizeof(uint32_t)];
				socket->recibir( puntuacion, sizeof(uint32_t) );
				//TODO FALTA VER QUE SE HACE CON LA "RAZON" DE PORQUE FINALIZO EL NIVEL
				modelo->setFinalizoNivel( true );
				modelo->setPuntuacion( (int)(*puntuacion) );
				break;
			}	
			case Mensaje::QUIT_TYPE:
			{
				std::cout<< "Quit\n";
				modelo->setFinalizoJuego( true );
				modelo->getEnviarMensaje()->enviarMensaje( new Key(4) );
				break;
			}	
			default: 
			{
				std::cout << "No se reconoce el tipo\n";
				continue;
			}
		} 
	}
	delete []buffer;
}

void RecibirMensaje::agregarElemento( PktElemento *pktElemento )
{
	int tipo = (int)pktElemento->tipo;
	Orientacion orientacion = (Orientacion)pktElemento->orientacion;
	int posicion = (int)pktElemento->posicion;
	Coordenada coord = this->buscarCoordenada( posicion );

	switch( tipo )
	{
		case (int)tSalidaPacman:
		{
			Modelo::getInstance()->setSalidaPacMan( new SalidaPacMan(posicion, coord, orientacion) );
			break;
		}
		case (int)tCasaFantasmas:
		{			
			Modelo::getInstance()->setCasaFantasmas(  new CasaFantasmas( posicion, coord, orientacion) );
			break;
		}
		case (int)tPowerup:
		{
			Modelo::getInstance()->getPowers().push_back( new PowerUp( posicion, coord, orientacion) );			
			break;
		}
		case (int)tBonus: 
		{
			Modelo::getInstance()->getBonus().push_back( new Bonus( posicion, coord, orientacion) );
			break;			
		}
		case (int)tPastilla:
		{
			Modelo::getInstance()->getPastillas().push_back( new Pastilla( posicion, coord, orientacion) );
			break;
		}
		default: {return;}
	}
}

void RecibirMensaje::recibirElementos( int cantElementos )
{
	int tamanio = cantElementos*sizeof(PktElemento);
	char *buffer = new char[tamanio];
	socket->recibir( buffer, tamanio );
	int delta = 0;
	for( int i=0; i<cantElementos; i++ )
	{
		PktElemento *pktElemento = (PktElemento*) (buffer + delta);
		agregarElemento( pktElemento );
		delta += sizeof(PktElemento);
	}
	delete []buffer;
}

//void imprimir( int **mat, int alto, int ancho)
//{
//	for( int i=0; i<alto; i++ )
//	{
//		for( int j=0; j<ancho; j++ )
//			std::cout << mat[i][j] << " ";
//		std::cout << " \n";
//	}
//}

int getbit( int x, char* buffer )
{
	uint8_t *byte = (uint8_t*)buffer;
	byte = byte + x / 8;
	unsigned mask = 1 << (7 - x % 8);
	if (*byte & mask)
		return 1;
	return 0;
}

void RecibirMensaje::recibirMapa( int ancho, int alto )
{	
	//Calculo la cantidad de bytes que hay que recibir
	int sizePadding = (8-(ancho*alto*2 )%8) %8; 
	int tamanio = ( (ancho*alto*2)  + sizePadding  )/8;
	char *buffer = new char[ tamanio ];
	//Recibo los bytes con la informacion del mapa
	socket->recibir( buffer, tamanio );
	//Aloco memoria para las matrices que representan las paredes verticales y horizontales del mapa
	int **ph = new int*[alto+1]; //Matriz que representa las paredes horizontales
	int **pv = new int*[alto]; //Matriz que representa las paredes verticales
	for( int i=0; i<alto; i++ )
	{
		ph[i] = new int[ancho];
		pv[i] = new int[ancho+1];
	}
	ph[alto] = new int[ancho];

	int j = 0;
	int numFila = 0;
	while( j < (ancho*alto*2) )
	{
		//Veo el rango de bits que representa los arcos norte
		for( int i=0; i< ancho; i++)
		{
			//Si no hay arco (bit = 0 ) entonces hay pared
			ph[numFila][i] = 1 - getbit( j, buffer );
			j++;
		}
		//Veo el rango de bits que representa los arcos este
		for( int i=0; i< ancho; i++ )
		{
			//Si no hay arco (bit = 0 ) entonces hay pared
			pv[numFila][i+1] = 1 - getbit(j, buffer );
			j++;
		}
		numFila++;
	}
	
	//seteo la pared horizontal de abajo
	for( int i=0; i<ancho; i++ )
	{
		ph[alto][i] = ph[0][i];
	}
	//seteo la pared vertical de la izquierda
	for( int i=0; i<alto; i++)
	{
		pv[i][0] = pv[i][ancho];
	}
	Mapa* mapa = new Mapa(ph, pv, ancho, alto ); 
	Modelo::getInstance()->setMapa( mapa );
	delete []buffer;
}

void RecibirMensaje::recibirInit( PktCabecera *cabecera )
{
	//Recibo el ancho y alto del mapa
	char *buffer = new char[sizeof(uint16_t)];
	socket->recibir( buffer, sizeof(uint16_t) );
	int ancho = (uint8_t)(*buffer);
	int alto = (uint8_t)(*(buffer + sizeof(uint8_t) ) );
	
	//Recibo el mapa
	recibirMapa( ancho, alto );
	
	crearVerticesMapa();
	//Recibo la cantidad de elementos que hay en el mapa
	uint16_t cantElementos;
	socket->recibir( (char*)(&cantElementos), sizeof(uint16_t) );
	cantElementos = ntohs(cantElementos);
	std::cout << "Cant elementos: " << (int)cantElementos << std::endl;
	
	//Recibo los elementos del mapa
	recibirElementos( cantElementos );
	delete []buffer;
}

void RecibirMensaje::recibirElementosStatus( int cantElementos )
{
	Modelo* modelo = Modelo::getInstance();
	int tamanio = cantElementos*sizeof(PktElementoStatus);
	char *elementos = new char[ tamanio ];
	socket->recibir( elementos, tamanio );
	int delta = 0;
	for( int i=0; i< cantElementos; i++ )
	{
		PktElementoStatus *elementoStatus = (PktElementoStatus*)(elementos + delta);
		if( elementoStatus->estado == Aparece )
		{
			PktElemento pktElemento;
			pktElemento.tipo = elementoStatus->tipo;
			pktElemento.orientacion = elementoStatus->orientacion;
			pktElemento.posicion = elementoStatus->posicion;
			agregarElemento( &pktElemento );
		}
		else //estado == Desaparece
		{
			Elemento* elemento = modelo->getElemento( (tipoElemento)elementoStatus->tipo, elementoStatus->posicion );
			elemento->setEstado( Desaparece );
		}
		delta += sizeof(PktElementoStatus);
	}
	delete []elementos;
}

int RecibirMensaje::getIdVertice( int idArista, int direccion, int anchoMapa )
{
	int ancho = Modelo::getInstance()->getMapa()->getAncho();
	int alto = Modelo::getInstance()->getMapa()->getAlto();
	int idVertice = 0;
	for(int i=0; i<alto; i++)
	{
		for( int j=0; j<ancho; j++)
		{
			//Chequeo para el caso de que sea arista Norte
			if( idArista == idVertice + i*ancho  )
			{
				//Si la direccion es sur entonces el vertice origen es idVertice-anchoMapa
				if( direccion == 0 )
					idVertice -= anchoMapa;
				return idVertice;
			}
			//Chequeo para el caso de que sea arista Este
			if( idArista == idVertice + (i+1)*ancho )
			{
				//Si la direccion es oeste entonces el vertice origen es el siguiente
				if( direccion == 0 )
					idVertice++;
				return idVertice;
			}
			idVertice++;
		}
	}
	return -1;
}


int calcularEje(int idVertice,int idArista,int ancho) {
	int fila=idVertice/ancho;
	if (idArista==idVertice+fila*ancho || idArista==idVertice+ancho*(fila+2)) return 1;
	else return 2;
	
}


float calcularIncremento(int posicionArista) {
	if (posicionArista!=0) {
		return ((posicionArista+1)/64.0)*LONGVERTICE;	
	}
	return 0;

}

void RecibirMensaje::recibirPosiciones( int cantJugadores )
{
	int tamanio = cantJugadores*sizeof(PktPosiciones);
	char *posiciones = new char[ tamanio ];
	socket->recibir( posiciones, tamanio );
	
	int delta = 0;
	for( int i=0; i<cantJugadores; i++ )
	{
		Modelo *modelo = Modelo::getInstance();
		PktPosiciones *pktPosicion = (PktPosiciones*)(posiciones + delta);
		int idJugador = (int)pktPosicion->id;
		int idArista = (int)pktPosicion->arista;
		int posicionArista = (int)pktPosicion->posicion;
		int direccion = (int)pktPosicion->direccion;
		int idVertice = getIdVertice( idArista, direccion, modelo->getMapa()->getAncho() );
		
		Posicion posicion( idVertice, idArista, posicionArista, direccion );
		
		Coordenada coordT;
		Coordenada coordCentro;
		
		Personaje *personaje = modelo->getPersonaje( idJugador);		
			
		//Si el jugador no existe, lo agrega. 
		if( personaje == NULL )
		{
			if( idJugador == 0 )
				personaje = new PacMan();
			else
				personaje = new Fantasma();
		}
				
			
		//Arista arista = buscarAristaPacman(ep.idArista);
		Coordenada coordInicial=buscarCoordenada(idVertice);
		float incremento = calcularIncremento(posicionArista);
		if (calcularEje(idVertice,idArista,modelo->getMapa()->getAncho())==2) {

			
			coordT.x=coordInicial.x+incremento;
			coordT.y=coordInicial.y;
			coordT.z=coordInicial.z;		
			
					
			if (direccion==1) {
				coordCentro.x = coordT.x + 1;					
			} else { //direccion=0 izquierda 
				coordCentro.x = coordT.x - 1;
			}
			coordCentro.y = coordT.y;
			coordCentro.z = coordT.z;				
			//cout<<"avanzo a Ojo: "<<posPacman.x<<" "<<posPacman.y<<"  "<<posPacman.z<<endl;
			//cout<<"avanzo a Centro: "<<posCentro.x<<" "<<posCentro.y<<"  "<<posCentro.z<<endl<<endl;
			
		}
		else {
			
			coordT.x=coordInicial.x;
			coordT.y=coordInicial.y;
			coordT.z=coordInicial.z-incremento;
			
			
			if (direccion==1) {
				coordCentro.z = coordT.z - 1; // porque avanza en la parte negativa del eje z
			} else { //direccion=0 izquierda 
				coordCentro.z = coordT.z + 1;
			}
			coordCentro.x = coordT.x;
			coordCentro.y = coordT.y;
			
			//cout<<"2-avanzo a Ojo: "<<posPacman.x<<" "<<posPacman.y<<"  "<<posPacman.z<<endl;
			//cout<<"2-avanzo a Centro: "<<posCentro.x<<" "<<posCentro.y<<"  "<<posCentro.z<<endl<<endl;
					
		}
		//camara.setOjo(coordT);//TODO extern de cliente.cpp
		//camara.setCentro(coordCentro);
		
		//personaje->SetCoordenadaR(coordR);
		personaje->SetCoordenadaT(coordT);
		//Actualiza la posicion
		personaje->SetPosicion(posicion);
		
		
		Model* model = new Model();
		ObjLoader::cargarModelo(*model,OBJ_PATH_PACMAN,TEX_PATH_PACMAN);
		personaje->SetModel( model);
		
		if( idJugador == 0 )
			Modelo::getInstance()->getPersonajes().push_back(personaje);
		else
			Modelo::getInstance()->getPersonajes().push_back(personaje );
		
		
		
				
				
				
		delta += sizeof(PktPosiciones);
	}
	delete []posiciones;
}

void RecibirMensaje::recibirStatus( PktCabecera *cabecera )
{
	
	Modelo *modelo = Modelo::getInstance();
	//Recibo la puntuacion
	int puntuacion;
	socket->recibir( (char*)&puntuacion, sizeof(uint32_t) );
	puntuacion = ntohl(puntuacion);
	modelo->setPuntuacion( puntuacion );
		
	//Recibo las posiciones de los jugadores
	recibirPosiciones( ((int)cabecera->aux)+1 );
	
	//Recibo la cantidad de elementos
	char *buffer = new char[sizeof(uint8_t)];
	socket->recibir( buffer, sizeof(uint8_t) );
 
	//Recibo los elementos
	recibirElementosStatus( (int)(*buffer) );
	delete []buffer;
}

void RecibirMensaje::crearVerticesMapa()
{
	Coordenada pos;
	int filas=Modelo::getInstance()->getMapa()->getAlto();
	int cols =Modelo::getInstance()->getMapa()->getAncho();
	
	int id;
	for( int i=0; i<filas; i++ )
	{
		for( int j=0; j<cols; j++ )
		{
			
			pos.x= j*LONGVERTICE+1;
			pos.y= ALTURAITEMS;
			pos.z= -(i*LONGVERTICE+1); 
			id = ((filas-1)-i)*cols+j;
			Vertice vert(id,pos);
			vecVertices.push_back(vert);
		}
	}
}

Coordenada RecibirMensaje::buscarCoordenada(int idVert) 
{
	Coordenada coord;
	int id;
	size_t i = 0;
	bool encontrado = false;
	while( !encontrado && i<vecVertices.size() )
	{
		id = vecVertices[i].getIdVertice();	
		if ( id == idVert ) 
		{
			coord = vecVertices[i].getCoordenada();
			encontrado = true;
		}
		else 
		{
			i++;
		}
	}
	return coord;
}
