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
	//this->elementos = new tList
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

	this->eliminarListaJugadores();
	//this->eliminarListaBonus();
	//this->eliminarListaElementos();
	delete mundo;
}
/*----------------------------------------------------------------------------*/
void Modelo::eliminarListaJugadores()
{
	itListJugadores it;
	
	for(it=jugadores.begin();it!=jugadores.end();it++)
		delete *it;
	jugadores.clear();
}
/*----------------------------------------------------------------------------*/
void Modelo::eliminarListaBonus()
{
	tListElementos::iterator it;
	for( it = bonus.begin(); it != bonus.end(); it++ )
	{
		std::cout<<"Elimina Bonus:"<<(*it)->getPosicion()<<"\n";
		delete (*it);
		(*it)=NULL;
	}
	bonus.clear();
}
/*----------------------------------------------------------------------------*/
void Modelo::eliminarListaElementos()
{
	tListElementos::iterator it;
	for( it = elementos.begin(); it != elementos.end(); it++ )
	{
		std::cout<<"Elimina elemento:"<<(*it)->getPosicion()<<"\n";
		delete (*it);
		(*it)=NULL;
	}

	elementos.clear();
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
			break;
		}
	}
	m_jugadores.unlock();
}
/*----------------------------------------------------------------------------*/
void Modelo::agregarElemento( Elemento * elemento )
{
	m_elemento.lock();
	this->elementos.push_back(elemento);
	m_elemento.unlock();
}
/*----------------------------------------------------------------------------*/
void Modelo::quitarElemento( int idPosicion )
{
	tListElementos::iterator it;
	m_elemento.lock();
	for( it = elementos.begin(); it != elementos.end(); it++ )
	{
		if( (*it)->getPosicion() == idPosicion )
		{
			delete (*it);
			elementos.erase( it );
			break;
		}
	}
	m_elemento.unlock();
}
/*----------------------------------------------------------------------------*/
void Modelo::agregarBonus( Elemento * bonus )
{
	m_bonus.lock();
	this->bonus.push_back(bonus);
	m_bonus.unlock();
}
/*----------------------------------------------------------------------------*/
Elemento* Modelo::getBonus( int idPosicion )
{
	tListElementos::iterator it;
	Elemento* elemento = NULL;
	m_bonus.lock();
	for( it = bonus.begin(); it != bonus.end(); it++ )
	{
		if((*it)->getPosicion()==idPosicion)
		{
			elemento =  (*it);
		}
	}
	m_bonus.unlock();
	return elemento;
}
/*----------------------------------------------------------------------------*/
void Modelo::cambiarSiguienteNivel()
{
	this->mundo->getNiveles()->pop();
	
	//Agrega los jugadores al proximo nivel en caso de haber.
	tListJugadores::iterator it;
	Jugador* jugador = NULL;
	if(this->hayNiveles())
	{
		m_jugadores.lock();
		for( it = jugadores.begin(); it != jugadores.end(); it++ )
		{
			jugador = (*it);
			AgregarJugadorOp* agregar = new AgregarJugadorOp(jugador);
			this->agregarOperacion(agregar);
		}
		m_jugadores.unlock();
	}
	
}
/*----------------------------------------------------------------------------*/
bool Modelo::estaJugando(Jugador* jugador)
{
	tListJugadores::iterator it;
	bool esta = false;
	m_jugadores.lock();
	for( it = jugadores.begin(); it != jugadores.end(); it++ )
	{
		if((*it)->GetIdJugador()== jugador->GetIdJugador())
			esta=true;
	}
	m_jugadores.unlock();
	return esta;
}
/*----------------------------------------------------------------------------*/
void Modelo::quitarBonus( int idPosicion )
{
	tListElementos::iterator it;
	m_bonus.lock();
	for( it = bonus.begin(); it != bonus.end(); it++ )
	{
		if( (*it)->getPosicion() == idPosicion )
		{
			delete (*it);
			bonus.erase( it );
			break;
		}
	}
	m_bonus.unlock();
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
 * Lista de bonus
 */
tListElementos* Modelo::GetBonus(){

	return &bonus;
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
Elemento* Modelo::getElemento( int posicion )
{
	itListElementos it;
	Elemento* elemento = NULL;
	m_elemento.lock();
	for(it=elementos.begin();it!=elementos.end();it++)
	{
		Estado estado = (*it)->getEstado();
		if((*it)->getPosicion() == posicion && estado!=Eliminado)
		{
			elemento=(*it);
			break;
		}
	}
	m_elemento.unlock();
	return elemento;
}
/*----------------------------------------------------------------------------*/
Jugador* Modelo::getJugador( int idJugador )
{
	itListJugadores it;
	Jugador* jugador = NULL;
	m_jugadores.lock();
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		if( (*it)->GetIdJugador() == idJugador )
		{
			jugador=(*it);
			break;
		}
	}
	m_jugadores.unlock();
	return jugador;
}
/*----------------------------------------------------------------------------*/
void Modelo::eliminarPersonajes()
{
	itListJugadores it;
	m_jugadores.lock();
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
	    Personaje* personaje = (*it)->getPersonaje();
		delete personaje;
		personaje=NULL;
	}
	m_jugadores.unlock();
}
/*----------------------------------------------------------------------------*/
int Modelo::GetPuntuacion()
{
	return getPacMan()->getPuntaje();
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
	
	//Si no termino el juego y hay niveles. 
	while(!this->seFinalizoElJuego() || this->hayNiveles())
	{
		//Obtener el mapa del nivel.
		string mapaPath = this->mundo->getNiveles()->front();
		this->mapa = XmlParser::getMapa(mapaPath);
		
		this->esperarMinJugadores();
		
		this->seFinalizoElNivel(false);
		while(!this->seFinalizoElNivel())
		{
			std::cout<<"Procesando operaciones..\n";
			this->ejecutarOperaciones();
		}

		this->cambiarSiguienteNivel();		
	}
	std::cout<<"Termino el Juego..\n";
	//Libera el thread que inserta los jugadores al juego.
	this->liberarStartJugadores();
	//TODO:Liberar actualizar Juego
}

void Modelo::esperarMinJugadores()
{
	std::cout<<"Esperando comienzo de nivel..\n";
	if(this->GetJugadores().size() < Config::getInstance()->GetMinJugadores())
		this->esperarMinJugadoresEvent.esperar();
	std::cout<<"Jugando nivel..\n";
}

/*----------------------------------------------------------------------------*/
bool Modelo::hayNiveles()
{
	return !mundo->getNiveles()->empty();
}
/*----------------------------------------------------------------------------*/
void Modelo::liberarNivel()
{
	ActualizarJuego::getInstance()->join();
	delete ActualizarJuego::getInstance();
	
	this->eliminarListaBonus();
	this->eliminarPersonajes();
	this->eliminarListaElementos();
	
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
		this->desacolar();	
		this->actualizarJuego();
		
		/* Espera la proxima operacion */
		this->esperarRecibirOperaciones();
	}
}
/*----------------------------------------------------------------------------*/
void Modelo::actualizarJuego()
{
	if(!this->seFinalizoElNivel())
		ActualizarJuego::getInstance()->run();
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
 * Lista de bonus
 */
void Modelo::SetBonus(tListElementos& bonus){

	this->bonus = bonus;
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
 * Obtiene de la lista de jugadores el personaje pacman.
 */
PacMan* Modelo::getPacMan()
{
	tListJugadores jugadores=this->GetJugadores();
	itListJugadores it;
	
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		Jugador* jugador = *it;
		if(jugador->GetIdPersonaje()==PacMan::PACMAN_TYPE)
		{
			PacMan* pacman = (PacMan*)jugador->getPersonaje();
			return pacman;
		}
	}
	return NULL;
}
/*----------------------------------------------------------------------------*/
void Modelo::comerElementoDelVertice(tVertice* vertice)
{
	PacMan* pacMan = this->getPacMan();
	//Busco pastillas
	Elemento* elemento = this->getElemento(vertice->getid());
	if(elemento == NULL)
	{
		//Si no encontro busca en bonus.
		elemento = this->getBonus(vertice->getid());
	}
	if(elemento != NULL)
	{
		if(elemento->getEstado()!=FueComido)
		{
			//Si encontro incrementa el puntaje y marca el estado FueComido
			pacMan->incPuntaje(elemento->getPuntaje());
			elemento->setEstado(FueComido);
			this->mostrarElementoComido(elemento);
		}
	}
	
}
/*----------------------------------------------------------------------------*/
void Modelo::mostrarElementoComido(Elemento* elemento)
{
	if(elemento->getTipo()==tPastilla)
		std::cout<<"PacMan come pastilla:" << elemento->getPosicion() << "\n";
	if(elemento->getTipo()==tPowerup)
		std::cout<<"PacMan come powerUp:" << elemento->getPosicion() << "\n";
	if(elemento->getTipo()==tBonus)
		std::cout<<"PacMan come bonus:" << elemento->getPosicion() << "\n";		
}
