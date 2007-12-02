///////////////////////////////////////////////////////////
//  Modelo.cpp
//  Implementation of the Class Modelo
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#include "Modelo.h"

Modelo* Modelo::pModelo = NULL;

Modelo* Modelo::getInstance () 
{
    if (pModelo == NULL)
    {  
    	pModelo = new Modelo(); 
    }
    return pModelo;
}
/*----------------------------------------------------------------------------*/
/**
 * Se setea una unica instancia del modelo.
 */
void Modelo::setInstance(pBool finalizoJuego,pBool cerroServidor)
{
	if (pModelo == NULL)
    {  
    	pModelo = new Modelo(finalizoJuego,cerroServidor);
    }
}
/*----------------------------------------------------------------------------*/
Modelo::Modelo(pBool finalizoJuego,pBool cerroServidor){
	this->finalizoJuego=finalizoJuego;
	this->cerroServidor=cerroServidor;
	this->puntuacion = 0;
}
/*----------------------------------------------------------------------------*/
Modelo::Modelo(){
	this->finalizoJuego=NULL;
	this->cerroServidor=NULL;
	this->puntuacion = 0;
}
/*----------------------------------------------------------------------------*/
Modelo::~Modelo(){
	tListJugadores jugadores=this->GetJugadores();
	itListJugadores it;
	
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		Jugador* jugador = *it;
		delete jugador;
	}
	jugadores.clear();
}
/*----------------------------------------------------------------------------*/
/**
 * Coloca la operacion en la cola.
 */
void Modelo::agregarOperacion(Operacion* operacion){
	this->operaciones.push(operacion);
	/* Avisa al modelo que llego una operacion */
	this->getRecibiOperacionEvent().activar(); 
}
/*----------------------------------------------------------------------------*/
/**
 * Lista de elementos del mapa.
 */
tListElementos* Modelo::GetElementos(){

	return &elementos;
}
/*----------------------------------------------------------------------------*/
/**
 * Nivel que se esta jugando actualmente.
 */
Mapa* Modelo::GetMapa(){

	return mapa;
}
/*----------------------------------------------------------------------------*/
/**
 * Lista de jugadores puede ser PacMan o Fantasma
 */
tListJugadores& Modelo::GetJugadores(){
	return this->jugadores;
}
/*----------------------------------------------------------------------------*/
int Modelo::GetPuntuacion()const
{
	return puntuacion;
}
/*----------------------------------------------------------------------------*/
/**
 * Ejecucion del hilo.
 */
void Modelo::main(){
	//Obtener el mundo.
	//this->mundo = XmlParser::getMundo(Config::getInstance()->GetMundoXmlPath());
	
	while(!this->seFinalizoElJuego())
	{
		//Obtener el mapa del nivel.
		//this->mapa = XmlParser::getMapa(Mundo->nivel->mapaPath);
		//Crear mensaje init
		
		std::cout<<"Esperando comienzo de nivel..\n";
		this->esperarMinJugadoresEvent.esperar();
		
		this->finalizoNivel=false;
		while(!this->finalizoNivel)
		{
			
			std::cout<<"Procesando operaciones..\n";
			this->ejecutarOperaciones();
			//Correr ActualizarEstado...
		}
		std::cout<<"Termino el nivel..\n";
	}
	std::cout<<"Termino el Juego..\n";
	//Libera el thread que inserta los jugadores al juego.
	this->liberarStartJugadores();
}
/*----------------------------------------------------------------------------*/
void Modelo::liberarStartJugadores()
{
	StartJugador::getInstance()->getRecibiStartEvent().activar();
	StartJugador::getInstance()->join();
	delete StartJugador::getInstance();
}
/*----------------------------------------------------------------------------*/
void Modelo::esperarRecibirOperaciones()
{
	if(operaciones.empty() && !seFinalizoElNivel())
	{
		//Espera a recibir operaciones.
		this->getRecibiOperacionEvent().esperar();
	}
}
/*----------------------------------------------------------------------------*/
/**
 * Desacola una operacion de la cola y la ejecuta.
 */
void Modelo::ejecutarOperaciones(){
	this->esperarRecibirOperaciones();
	
	while(!this->operaciones.empty())
	{	
		Operacion* operacion=getOperacion();
		operacion->ejecutar(this);
		
		/*tListJugadores jugadores;
		itListJugadores it;
		jugadores = this->GetJugadores();
		for(it=jugadores.begin();it!=jugadores.end();it++)
		{
			std::cout<<"Esta jugando el jugador:"<<(*it)->GetIdJugador()<<"\n";
		}*/
		
		this->desacolar();
		//Mutex());

		/* Espera la proxima operacion */
		this->esperarRecibirOperaciones();
	}
}
/*----------------------------------------------------------------------------*/
Operacion* Modelo::desacolar()
{
	Operacion* operacion=this->operaciones.front();
	delete operacion;
	this->operaciones.pop();
	return operacion;
}
/*----------------------------------------------------------------------------*/
Operacion* Modelo::getOperacion()
{
	return this->operaciones.front();
}
/*----------------------------------------------------------------------------*/
/**
 * Notifica que los jugadores deben actualizar el estado
 */
void Modelo::notify(){

}
/*----------------------------------------------------------------------------*/
/**
 * Lista de elementos del mapa.
 */
void Modelo::SetElementos(tListElementos& elementos){

	this->elementos = elementos;
}
/*----------------------------------------------------------------------------*/
/**
 * Lista de elementos del jugadores.
 */
void Modelo::SetJugadores(tListJugadores& jugadores){

	this->jugadores = jugadores;
}
/*----------------------------------------------------------------------------*/
/**
 * Nivel que se esta jugando actualmente.
 */
void Modelo::SetMapa(Mapa *mapa)
{
	this->mapa = mapa;
}
/*----------------------------------------------------------------------------*/
/**
 * Puntuacion del pacman
 */
void Modelo::SetPuntuacion( int puntuacion )
{
	this->puntuacion = puntuacion;
}
