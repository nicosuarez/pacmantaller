///////////////////////////////////////////////////////////
//  AgregarJugadorOp.cpp
//  Implementation of the Class AgregarJugadorOp
//  Created on:      21-Nov-2007 23:40:17
///////////////////////////////////////////////////////////

#include "AgregarJugadorOp.h"


AgregarJugadorOp::AgregarJugadorOp(Jugador* jugador){
	this->jugador=jugador;
}

/**
 * Valida y aplica la operacion* retorna TRUE(exito),FALSE(error)
 */
bool AgregarJugadorOp::ejecutar()
{
	//Se le asigna un personaje al jugador
	this->asignarPersonaje();
	//Se le envia al cliente el paquete init
	this->enviarMsgInit();
	//Se espera 5 segundos y se envia el mensaje start agregando el jugador 
	//a la lista del modelo
	Play* play = new Play(this->jugador);
	play->run();
	StartJugador::getInstance()->agregarStart(play);

	return false;
}

void AgregarJugadorOp::enviarMsgInit()
{
	Socket *socket = jugador->GetSocket();
	int rol=jugador->getPersonaje()->GetRol();
	Init init(rol);
	char *buffer = init.Serialize();
	//socket->enviar( buffer, init.getSize());
	
	socket->enviar( buffer, sizeof(PktInit) );
	int delta = sizeof(PktInit);
	
	Mapa *mapa = Modelo::getInstance()->GetMapa();
	int cantAristas = mapa->getAlto()*mapa->getAncho()*2;
	int sizeGrafo = (  cantAristas + ( 8 - cantAristas%8 )%8  )/8;
	
	for(int i=0; i< sizeGrafo; i++ )
	{
		socket->enviar( buffer+delta, 1 );
		delta ++;
	}
	uint16_t cantElementos = (uint16_t) ( *(buffer + delta) );
	cantElementos = htons( cantElementos );
	socket->enviar( (char*) &cantElementos, sizeof(uint16_t) );
	delta += sizeof(uint16_t);
	cantElementos = ntohs( cantElementos );
	int sizeElementos = ( (int)cantElementos )*sizeof(PktElemento);
	socket->enviar( buffer+delta, sizeElementos );
	delete[] buffer;
}

//Retorna el rol que se le asgino al jugador
void AgregarJugadorOp::asignarPersonaje()
{
	if(jugador->GetIdJugador() == PacMan::PACMAN_TYPE)
	{
		//Setea la posicion incial de los personajes en el mapa 
		this->initPacMan();
	}
	else 
	{
		//Setea la posicion incial de los personajes en el mapa 
		this->initFantasma();
	}
}

void AgregarJugadorOp::initPacMan()
{
	int idVertice = -1;

	//Obtener la posicion de salida del pacman
	idVertice = Modelo::getInstance()->getSalidaPacMan()->getPosicion();
	
	Posicion posicion = this->getPosicionInicialPacman();

	//Se setea el personaje al jugador
	Personaje* personaje = new PacMan(posicion);
	jugador->SetIdPersonaje(PacMan::PACMAN_TYPE);
	
	jugador->SetPersonaje( personaje );
	
	std::cout<<"Entra PacMan al juego. ID:"<< jugador->GetIdJugador()<<"\n";
}

Posicion AgregarJugadorOp::getPosicionInicialPacman()
{
	Modelo* modelo = Modelo::getInstance();
	int idVertice = modelo->getSalidaPacMan()->getPosicion();
	
	tVertice* vSalida = modelo->GetMapa()->getGrafo()->getVertice(idVertice);
	
	//Toma el primer arco
	tArco* aristaSalida = vSalida->getArcos()->front();
    
	int aristaId = aristaSalida->getid();
	Orientacion orientacion = aristaSalida->getElemento();
	int direccion=Posicion::getDireccionInicial(orientacion);
	int posArista = Posicion::getPosAristaInicial(direccion);
    
	Posicion posicion(idVertice,aristaId,posArista,direccion);
	return posicion;
}

Posicion AgregarJugadorOp::getPosicionInicialFantasmas()
{
	Modelo* modelo = Modelo::getInstance();
	int idVertice = modelo->getCasaFantasmas()->getPosicion();
	Orientacion orientacion = modelo->getCasaFantasmas()->getOrientacion();
	
	tVertice* vSalida = modelo->GetMapa()->getGrafo()->getVertice(idVertice);
	
	//Toma el arco se la orientacion de la casa
	tArco* aristaSalida = vSalida->getArco(orientacion);
    
	int aristaId = aristaSalida->getid();
	int direccion=Posicion::getDireccionInicial(orientacion);
	int posArista = Posicion::getPosAristaInicial(direccion);
    
	Posicion posicion(idVertice,aristaId,posArista,direccion);
	return posicion;
}


void AgregarJugadorOp::initFantasma()
{
	int idVertice=-1;
	
	//Obtener la posicion de salida del fantasmas (casa)
	idVertice = Modelo::getInstance()->getCasaFantasmas()->getPosicion();
	Posicion posicion = this->getPosicionInicialFantasmas();

	//Se setea el personaje al jugador
	Personaje* personaje = new Fantasma(posicion);
	jugador->SetIdPersonaje(Fantasma::FANTASMA_TYPE);
	jugador->SetPersonaje( personaje );
	
	std::cout<<"Entra Fantasma al juego. ID:"<< jugador->GetIdJugador()<<"\n";
}


