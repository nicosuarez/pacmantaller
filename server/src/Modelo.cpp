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
Modelo::Modelo(pBool finalizoJuego,pBool cerroServidor):dispatcher(&jugadores, finalizoJuego, &m_jugadores){
	this->finalizoJuego=finalizoJuego;
	this->cerroServidor=cerroServidor;
	this->puntuacion = 0;
	this->dispatcher.run();
}
/*----------------------------------------------------------------------------*/
Modelo::Modelo():dispatcher(&jugadores, finalizoJuego, &m_jugadores){
	this->finalizoJuego=NULL;
	this->cerroServidor=NULL;
	this->puntuacion = 0;
	this->dispatcher.run();
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
	
	delete mundo;
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
void Modelo::agregarJugador( Jugador *jugador )
{
	m_jugadores.lock();
	jugadores.push_back(jugador);
	m_jugadores.unlock();
}

/*----------------------------------------------------------------------------*/
void Modelo::quitarJugador( int idJugador )
{
	tListJugadores::iterator it;
	m_jugadores.lock();
	for( it = jugadores.begin(); it != jugadores.end(); it++ )
	{
		if( (*it)->GetIdJugador() == idJugador )
		{
			delete (*it);
			jugadores.erase( it );
			return;
		}
	}
	m_jugadores.unlock();
}

/*----------------------------------------------------------------------------*/
/**
 * Posicion de salida del PacMan
 */
void Modelo::SetSalidaPacMan(SalidaPacMan& salidaPacMan)
{
	this->salidaPacMan=salidaPacMan;
}
/*----------------------------------------------------------------------------*/
/**
 * Casa de los fantasmas, posicion de salida de los mismos
 */
void Modelo::SetCasaFantasmas(CasaFantasmas& casaFantasmas)
{
	this->casa=casaFantasmas;
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
 *  Retorna el mundo que se esta jugando actualmente
 */
Mundo* Modelo::GetMundo()
{
	return this->mundo;
}
/*----------------------------------------------------------------------------*/
/**
 * Lista de jugadores puede ser PacMan o Fantasma
 */
tListJugadores& Modelo::GetJugadores(){
	return this->jugadores;
}

/*----------------------------------------------------------------------------*/

Jugador* Modelo::getJugador( int idJugador )
{
	itListJugadores it;
	Jugador* jugador = NULL;
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		if( (*it)->GetIdJugador() == idJugador )
		{
			jugador=(*it);
			break;
		}
	}
	return jugador;
	
}

/*----------------------------------------------------------------------------*/
int Modelo::GetPuntuacion()const
{
	return puntuacion;
}

/*----------------------------------------------------------------------------*/

Dispatcher* Modelo::getDispatcher()
{
	return &dispatcher;
}

/*----------------------------------------------------------------------------*/

Mutex& Modelo::getMutexJugadores()
{
	return m_jugadores;
}

/**
 * Ejecucion del hilo.
 */
void Modelo::main(){
	//Obtener el mundo.
	this->mundo = XmlParser::getMundo(Config::getInstance()->GetMundoXmlPath());
	
	while(!this->seFinalizoElJuego())
	{
		//Obtener el mapa del nivel.
		string mapaPath = this->mundo->getNiveles()->front();
		this->mapa = XmlParser::getMapa(mapaPath);
		//Crear mensaje init
		
		std::cout<<"Esperando comienzo de nivel..\n";
		this->esperarMinJugadoresEvent.esperar();
		
		this->seFinalizoElNivel(false);
		while(!this->seFinalizoElNivel())
		{
			std::cout<<"Procesando operaciones..\n";
			this->ejecutarOperaciones();
		}
		this->mundo->getNiveles()->pop();
		liberarNivel();
		std::cout<<"Termino el nivel..\n";
	}
	std::cout<<"Termino el Juego..\n";
	//Libera el thread que inserta los jugadores al juego.
	this->liberarStartJugadores();
}
/*----------------------------------------------------------------------------*/
void Modelo::liberarNivel()
{
	ActualizarJuego::getInstance()->join();
	delete ActualizarJuego::getInstance();
	
	tListElementos* elementos;
	itListElementos it;
	elementos = this->GetElementos();
	for(it=elementos->begin();it!=elementos->end();it++)
	{
		std::cout<<"Elimina elemento:"<<(*it)->getPosicion()<<"\n";
		delete (*it);
	}
	
	delete mapa;
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
		operacion->ejecutar();
		/*tListJugadores jugadores;
		itListJugadores it;
		jugadores = this->GetJugadores();
		for(it=jugadores.begin();it!=jugadores.end();it++)
		{
			std::cout<<"Esta jugando el jugador:"<<(*it)->GetIdJugador()<<"\n";
		}*/
		
		this->desacolar();
		//Mutex());

		//Empieza actualizar el juego
		ActualizarJuego::getInstance()->run();
		
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
 * Mundo que se esta jugando actualmente
 */
void Modelo::SetMundo(Mundo *mundo)
{
	this->mundo = mundo;
}
/*----------------------------------------------------------------------------*/
/**
 * Puntuacion del pacman
 */
void Modelo::SetPuntuacion( int puntuacion )
{
	this->puntuacion = puntuacion;
}
/*----------------------------------------------------------------------------*/
/**
 * Obtiene de la lista de jugadores el personaje pacman.
 */
Personaje* Modelo::getPacMan()
{
	tListJugadores jugadores=this->GetJugadores();
	itListJugadores it;
	
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		Jugador* jugador = *it;
		if(jugador->GetIdPersonaje()==PacMan::PACMAN_TYPE)
			return jugador->getPersonaje();
	}
	return NULL;
}
