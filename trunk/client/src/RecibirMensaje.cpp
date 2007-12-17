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
	cout<<"empiezo a recibir msgs"<<endl;
	this->recibirMensaje();
}

void RecibirMensaje::recibirMensaje()
{
	Modelo *modelo = Modelo::getInstance();
	char *buffer = new char[sizeof(PktCabecera)];
	bool start=false;
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
				start=true;
				break;
			}	
			case Mensaje::STATUS_TYPE:
			{
				std::cout<< "Status\n";
				if(start)
					recibirStatus( cabecera );
				break;
			}	
			case Mensaje::STOP_TYPE:
			{
				std::cout<< "Stop\n";
				//recibo la puntuacion del pacman
				char puntuacion[sizeof(uint32_t)];
				socket->recibir( puntuacion, sizeof(uint32_t) );
				modelo->setPuntuacion( (int)(*puntuacion) );
				modelo->setFinalizoNivel( true );
				verRazon( cabecera->aux );
				break;
			}	
			case Mensaje::QUIT_TYPE:
			{
				std::cout<< "Quit\n";
				modelo->setFinalizoJuego( true );
				modelo->getEnviarMensaje()->enviarMensaje( new Key(KEY_ESCAPE) );
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
			cout<<" SETEO SALIDA PACMAN CON COORD "<<coord.x<<" "<<coord.y<<" "<<coord.z<<endl;
			Modelo::getInstance()->setSalidaPacMan( new SalidaPacMan(posicion, coord, orientacion) );
			break;
		}
		case (int)tCasaFantasmas:
		{			
			cout<<" SETEO CASA DE FANTASMA CON COORD "<<coord.x<<" "<<coord.y<<" "<<coord.z<<endl;
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
			std::cout<<"recibe bonus estado: Aparece"<<"\n";
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
			//************************
			if (numFila==0 && (1-ph[numFila][i])==1) {
				Modelo::getInstance()->getAristasPortal().push_back(j-1);//por el j++
				cout<<"arista= "<<j<<" es una arista PORTAL"<<endl;
			}
			//************************
		}
		//Veo el rango de bits que representa los arcos este
		for( int i=0; i< ancho; i++ )
		{
			//Si no hay arco (bit = 0 ) entonces hay pared
			pv[numFila][i+1] = 1 - getbit(j, buffer );
			j++;
			//************************
			if (i==(ancho-1) && (1-pv[numFila][i+1])==1) {
				Modelo::getInstance()->getAristasPortal().push_back(j-1);//por el j++
				cout<<"arista= "<<j<<" es una arista PORTAL"<<endl;
			}
			//************************
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
		
		int estado = elementoStatus->estado;
		int tipo = elementoStatus->tipo;
		std::cout<<"elemento tipo: "<<tipo <<" estado: "<< estado<<"\n";
		
		if( estado == Aparece )
		{
			std::cout<<"Aparece elemento tipo: "<<tipo<<"\n";
			PktElemento pktElemento;
			pktElemento.tipo = elementoStatus->tipo;
			pktElemento.orientacion = elementoStatus->orientacion;
			pktElemento.posicion = elementoStatus->posicion;
			agregarElemento( &pktElemento );
		}
		else
		{
			Elemento* elemento = modelo->getElemento( (tipoElemento)elementoStatus->tipo, elementoStatus->posicion );
			if(elemento!=NULL)
			{
				std::cout<<"Desaparece elemento tipo: "<<tipo<<"\n";
				elemento->setEstado( Desaparece );
			}
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


int RecibirMensaje::calcularEje(int idVertice,int idArista,int ancho) {
	
	int fila=idVertice/ancho;
	
	if (idArista==idVertice+fila*ancho || idArista==idVertice+ancho*(fila+2)) 
		return 1; //eje vertical
	else 
		return 2;//eje horizontal
	
}


float RecibirMensaje::calcularIncremento(int posicionArista) {
		
	if (posicionArista!=0) {
		return ((posicionArista+1)/64.0)*LONGVERTICE;	
	}
	return 0;

}


bool RecibirMensaje::esAristaPortal(int idArista) {
	
	bool existe = false;
	tListAristaPortal lista = Modelo::getInstance()->getAristasPortal();
	tListAristaPortal::iterator itLista= lista.begin(); 
	
	while (!existe && itLista!= lista.end()) {
		if (*itLista==idArista) {
			cout<<"&&&&& "<<idArista<<" ESSSSSSSSSS arista PORTAL"<<endl;
			existe = true;
		}
		else {
			cout<<"&&&&& "<<idArista<<" no es arista PORTAL"<<endl;
			itLista++;
		}
	}	
	return existe;
}


void RecibirMensaje::pasarPortal( int idJugador, Posicion posicion) {
	int eje = calcularEje( posicion.getVertice(),posicion.getArista(),Modelo::getInstance()->getMapa()->getAncho() );
	int idVerticeFinal;
	Coordenada coord,coordCentro;
	
	int ancho = Modelo::getInstance()->getMapa()->getAncho();
	int alto = Modelo::getInstance()->getMapa()->getAlto();
	
	if (eje==2) { //eje x
		cout<<"PORTAL---------------->EJE X"<<endl;
		if (posicion.getDireccion()==1) { //portal esta en la derecha del mapa
			cout<<"PORTAL-->EJE X---------->portal derecha del mapa"<<endl;
			idVerticeFinal = posicion.getVertice() - (ancho - 1) ;
			coord = buscarCoordenada(idVerticeFinal);
			coordCentro = coord;
			coordCentro.x += 1;
			
		}
		else { //portal de la izquierda
			cout<<"PORTAL-->EJE X---------->portal izquierda del mapa"<<endl;
			idVerticeFinal = posicion.getVertice() + (ancho - 1) ;
			coord = buscarCoordenada(idVerticeFinal);
			coordCentro = coord;
			coordCentro.x -= 1;
		}
		
	}
	else { //eje z
		cout<<"PORTAL---------------->EJE Z"<<endl;
		if (posicion.getDireccion()==1) { //portal de arriba
			cout<<"PORTAL-->EJE Z---------->portal arriba del mapa"<<endl;
			idVerticeFinal = (alto-1)*ancho + posicion.getVertice();
			coord = buscarCoordenada(idVerticeFinal);
			coordCentro = coord;
			coordCentro.z -= 1;
		}
		else { // portal de abajo
			cout<<"PORTAL-->EJE Z---------->portal abajo del mapa"<<endl;
			idVerticeFinal = posicion.getPosicionArista()%ancho;
			coord = buscarCoordenada(idVerticeFinal);
			coordCentro = coord;
			coordCentro.z += 1;
		}
		
	}
	
	if ( idJugador == Modelo::getInstance()->getid()) {
		cout<<"actualizo camara"<<endl;
		cout<<"coord "<<coord.x<<"  "<<coord.z<<"     coordCentro "<<coordCentro.x<<"  "<<coordCentro.z<<endl;
		Modelo::getInstance()->getCamara().setOjo(coord);
		Modelo::getInstance()->getCamara().setCentro(coordCentro);		
	}
	
	Personaje *personaje = Modelo::getInstance()->getPersonaje( idJugador);//NUNCA ES NULL
	//personaje->SetCoordenadaR(coordR);
	personaje->SetCoord(coord);
	//Actualiza la posicion
	personaje->SetPosicion(posicion);
		
}

void RecibirMensaje::agregarPersonaje(int idJugador, Posicion posicion) {

	Coordenada coordT;
	Coordenada coordCentro,coordOjo;
	bool agregarALista=false;
	Modelo *modelo = Modelo::getInstance();
	Personaje *personaje = modelo->getPersonaje( idJugador);		
	Coordenada coordInicial;
	
	
	//Si el jugador no existe, lo agrega. 
	if( personaje == NULL )
	{
			
		cout<<"no existe, agrego personaje"<<endl;
		agregarALista = true;
		Model* model = new Model;
		
		if( idJugador == 0 ) {
			personaje = new PacMan();
			//personaje->model=new Model;
//			cout<<"voy a cargar modelo pacman"<<endl;
			//ObjLoader::cargarModelo(*personaje->model,OBJ_PATH_PACMAN,TEX_PATH_PACMAN);
			ObjLoader::cargarModelo(*model,OBJ_PATH_PACMAN,TEX_PATH_PACMAN);
//			cout<<"cargue obj y tga de PACMAN"<<endl;	
			
			personaje->SetModel( model);
			//if (Modelo::getInstance()->getSalidaPacMan() ==NULL )  cout<<"ERROR"<<endl;
			//coordInicial = (Modelo::getInstance()->getSalidaPacMan())->getCoordenada();
			//cout<<"obtengo coord"<<endl;
			//cout<<"coordInicial: "<<coordInicial.x<<" "<<coordInicial.y<<" "<<coordInicial.z<<endl;*/
			
		}
		else{			
			personaje = new Fantasma();			
			//coordInicial = Modelo::getInstance()->getCasaFantasmas()->getCoordenada();
//			cout<<"voy a cargar modelo FANT"<<endl;			
			ObjLoader::cargarModelo(*model,OBJ_PATH_FANTASMA,TEX_PATH_FANTASMA);
//			cout<<"cargue obj y tga de FANTASMA"<<endl;			
			personaje->SetModel( model);			
			
		}
	}
	int posArista = posicion.getPosicionArista();
	

	if (! esAristaPortal(posicion.getArista())) {
		
		
		coordInicial = buscarCoordenada(posicion.getVertice());
	//	cout<<"coordInicial= "<<coordInicial.x<<" "<<coordInicial.y<<" "<<coordInicial.z<<endl;
		float incremento = calcularIncremento(posArista);
	//	cout<<"incremento= "<<incremento<<endl;
		
		int eje = calcularEje( posicion.getVertice(),posicion.getArista(),Modelo::getInstance()->getMapa()->getAncho() );
		
		coordT=coordInicial;
	//	cout<<"ESTE   ES   EL  EJE : "<<eje<<endl; 
		if ( eje == 2 ) {//eje X
	//		cout<<"ES EJE X! "<<endl;
					
			if (posicion.getDireccion()==1) {			
				//coordT.x=coordInicial.x+(LONGVERTICE-incremento);
				coordT.x=coordInicial.x+incremento;
											
			} else { //direccion=0 izquierda
				coordT.x=coordInicial.x - (LONGVERTICE-incremento);
				//coordT.x=coordInicial.x - incremento;
			}	
						
		}
		else { //eje Z
			//cout<<"ES EJEZ! "<<endl;
			if (posicion.getDireccion()==1) {			
				coordT.z=coordInicial.z-incremento;
											
			} else { //direccion=0 izquierda
				coordT.z=coordInicial.z + (LONGVERTICE-incremento);
				//coordT.z=coordInicial.z + incremento;
			}
				
		}
		
		
		if (idJugador == Modelo::getInstance()->getid()) {
			coordOjo = coordT;
			coordCentro = coordT;
			if ( eje==1 ) {
				//cout<<"#### ejez PARA CAMARA "<<endl;
				if (posicion.getDireccion()==1) {
					//coordOjo.z = coordT.z +0.5;
					coordCentro.z = coordT.z - 1; // porque avanza en la parte negativa del eje z
					//cout<<"##### ejez PARA CAMARA -->DIR==1 "<<endl;
				} else { //direccion=0 izquierda
					//coordOjo.z = coordT.z -0.5;
					coordCentro.z = coordT.z + 1;
					//cout<<"###### ejez PARA CAMARA --> DIR==0 "<<endl;
				}
	//			cout<<"2-avanzo a Ojo: "<<coordOjo.x<<" "<<coordOjo.y<<"  "<<coordOjo.z<<endl;
	//			cout<<"2-avanzo a Centro: "<<coordCentro.x<<" "<<coordCentro.y<<"  "<<coordCentro.z<<endl<<endl;			
			}
			else {
				//**************************
		//		cout<<"#######ejex PARA CAMARA "<<endl;
				if (posicion.getDireccion()==1) {
					//coordOjo.x = coordT.x + 0.5;
					coordCentro.x = coordT.x + 1;
			//		cout<<"##### ejex PARA CAMARA --> DIR==1 "<<endl;
					
				} else { //direccion=0 izquierda
					//coordOjo.x = coordT.x - 0.5;
					coordCentro.x = coordT.x - 1;
				//	cout<<"##### ejex PARA CAMARA --> DIR==0 "<<endl;
				}							
	//			cout<<"avanzo a Ojo: "<<coordOjo.x<<" "<<coordOjo.y<<"  "<<coordOjo.z<<endl;
	//			cout<<"avanzo a Centro: "<<coordCentro.x<<" "<<coordCentro.y<<"  "<<coordCentro.z<<endl<<endl;
			
			}
			
			//cout<<"actualizo camara"<<endl;		
			modelo->getCamara().setOjo(coordT);
			modelo->getCamara().setCentro(coordCentro);
		}
		
		//personaje->SetCoordenadaR(coordR);
		personaje->SetCoord(coordT);
		//Actualiza la posicion
		personaje->SetPosicion(posicion);
		
		
		if ( agregarALista ) {
			cout<<" push de personaje que no existia"<<endl;
			modelo->getMutexPersonajes().lock();
			modelo->getPersonajes().push_back(personaje);
			modelo->getMutexPersonajes().unlock();							
		}
	}
	else {
		pasarPortal(idJugador,posicion);					
	}
	
}

void RecibirMensaje::recibirPosiciones( int cantJugadores )
{	
	cout<<"cant Jugadores: "<<cantJugadores<<endl;
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
		
		//cout<<"INFO STATUS"<<endl;
		cout<<"IDJUG: "<<idJugador<<" IDARISTA: "<<idArista<<" POSARISTA: "<<posicionArista<<" DIR: "<<direccion<<"  "<<idVertice<<endl;
		Posicion posicion( idVertice, idArista, posicionArista, direccion );
		
		agregarPersonaje( idJugador, posicion);
				
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
		
	//cout<<"voy a entrar a recibir posiciones"<<endl;
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

void RecibirMensaje::verRazon( int razon )
{
	Modelo *modelo = Modelo::getInstance();
	switch( razon )
	{
		case PACMAN_GANO:
		{
			std::cout << "PACMAN GANO\n";
			modelo->eliminarBonus();
			modelo->eliminarPastillas();
			modelo->eliminarPowers();
			modelo->eliminarPersonajes();
			break;
		}
		case PACMAN_FUE_COMIDO:
		{
			std::cout << "EL PACMAN FUE COMIDO\n";
			break;
		}
		case PACMAN_SE_DESCONECTO:
		{
			std::cout << "EL PACMAN SE DESCONECTO\n";
			break;
		}
		case JUGADORES_INSUFICIENTES:
		{
			std::cout << "CANTIDAD DE JUGADORES INSUFICIENTES\n";
			break;
		}
		case SERVER_TERMINADO:
		{
			std::cout << "EL SERVIDOR FUE TERMINADO\n";
			break;
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
	//if (!encontrado) cout<<"NO PUEDE SER QUE NO EXISTA"<<endl;
	return coord;
}
