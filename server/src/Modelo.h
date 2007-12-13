///////////////////////////////////////////////////////////
//  Modelo.h
//  Implementation of the Class Modelo
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#if !defined(EA_C452893E_00CB_470e_BB7D_F33E91B1347A__INCLUDED_)
#define EA_C452893E_00CB_470e_BB7D_F33E91B1347A__INCLUDED_

#include <list>
#include <queue>
#include <string>
#include "Mutex.h"
#include "Elemento.h"
#include "Operacion.h"
#include "Jugador.h"
#include "AppSettings.h"
#include "Mapa.h"
#include "Mundo.h"
#include "Config.h"
#include "StartJugador.h"
#include "XmlParser.h"
#include "CasaFantasmas.h"
#include "Bonus.h"
#include "SalidaPacMan.h"
#include "Dispatcher.h"
#include "ActualizarJuego.h"

using std::string;

class Operacion;

typedef std::list<Elemento*> tListElementos; 
typedef std::queue<Operacion*> tQueueOperacion;
typedef std::list<Jugador*> tListJugadores;
typedef std::list<Jugador*>::iterator itListJugadores;
typedef std::list<Elemento*>::iterator itListElementos;
typedef bool* pBool;

/**
 * Clase que se controla el ciclo de vida del juego, aplicando diferentes
 * operaciones.
 */
class Modelo: public Thread
{

public:
	static Modelo* getInstance();
	
	static void setInstance(pBool finalizoJuego,pBool cerroServidor);
	
	//Agrega una operacion a la cola de operaciones
	void agregarOperacion(Operacion* operacion);
	
	//Agrega un jugador a la lista de jugadores
	void agregarJugador( Jugador *jugador );
	
	//Elimina el jugador del id pasado por parametro de la lista
	void quitarJugador( int idJugador );
	
	//Retorna la lista de elementos
	tListElementos* GetElementos();
	
	//Retorna un puntero al mapa
	Mapa* GetMapa();
	
	//Retorna un puntero al mundo
	Mundo* GetMundo();
	
	//Retorna un puntero al dispatcher
	Dispatcher* getDispatcher();
	
	//Retorna una referencia a la lista de jugadores
	tListJugadores& GetJugadores();
	
	//Retorna un puntero al jugador buscado, si no lo encuentra
	//retorna NULL
	Jugador* getJugador( int idJugador );
	
	//Retorna una referencia al mutex que protege la lista de jugadores
	Mutex& getMutexJugadores();
	
	//Retorna la puntuacion del Pacman
	int GetPuntuacion()const;
	
	//Ejecuta las operaciones
	void main();
	
	void notify();
	
	void SetElementos(tListElementos& elementos);
	
	void SetMapa(Mapa* mapa);
	
	void SetMundo(Mundo* mundo);
	
	void SetJugadores(tListJugadores& jugadores);
	
	void SetPuntuacion( int puntuacion );
	
	void seFinalizoElJuego(bool finalizo){*finalizoJuego=finalizo;};
	
	bool seFinalizoElJuego(){return *finalizoJuego;};
	
	void liberarStartJugadores();
	
	void liberarNivel();
	
	void SetSalidaPacMan(SalidaPacMan& salidaPacMan);
	
	Personaje* getPacMan();
	
	void SetCasaFantasmas(CasaFantasmas& casaFantasmas);
	
	SalidaPacMan* getSalidaPacMan(){return &salidaPacMan;} 
	
	CasaFantasmas* getCasaFantasmas(){return &casa;}
	
	/**
	 * Determina se termino el nivel o no
	 */
	bool seFinalizoElNivel(){return finalizoNivel;};
	
	//Setea el comiezo o el fin del nivel.
	void seFinalizoElNivel(bool finalizo){finalizoNivel=finalizo;};
	
	//Indica si el nivel ha finalizado o no
	pBool getFinalizoNivel(){return &finalizoNivel;};
	
	//Indica si el juego ha finalizado o no
	pBool getFinalizoJuego(){return finalizoJuego;};
	
	Operacion* getOperacion();
	
	Operacion* desacolar();
	
	//Pone a esperar el evento RecibiOperaciones
	void esperarRecibirOperaciones();
	
	//Destructor
	virtual ~Modelo();
	
	/* Eventos */
	Evento& getRecibiOperacionEvent(){return this->recibiOperacionEvent;};
	Evento& getEsperarMinJugadoresEvent(){return this->esperarMinJugadoresEvent;};
protected:
	Modelo();
	Modelo(pBool finalizoJuego,pBool cerroServidor);
	Modelo(const Modelo&);
	Modelo& operator= (const Modelo&);
	
private:
	static Modelo* pModelo;
	
	//Mutex que protege la lista de jugadores
	Mutex m_jugadores;
	
	//Salida del pacman.
	SalidaPacMan salidaPacMan;
	
	//Casa de los fantasmas posicion
	CasaFantasmas casa;
	
	//Evento que determina si hay que empezar el juego.
	Evento esperarMinJugadoresEvent;
	
	//Evento que determina si recibio una operacion
	Evento recibiOperacionEvent;
	
	//Lista de elementos del mapa.
	tListElementos elementos;
	
	//Mundo que se esta jugando actualmente.
	Mundo *mundo;
	
	// Nivel que se esta jugando actualmente.
	Mapa *mapa;
	
	//Lista de operacion que se ejecutan sobre el modelo
	tQueueOperacion operaciones;
	
	//Lista de jugadores pueden ser PacMan o Fantasma
	tListJugadores jugadores;
	
	//Indica si el nivel ha finalizado o no
	bool finalizoNivel;
	
	//Indica si el juego ha finalizado o no
	pBool finalizoJuego;
	
	//Indica si el servidor termino o no.
	pBool cerroServidor;
	 
	//Puntuacion del pacman
	int puntuacion;
	
	Dispatcher dispatcher;
	
	//Desacola una operacion de la cola y la ejecuta.
	void ejecutarOperaciones();
};
#endif // !defined(EA_C452893E_00CB_470e_BB7D_F33E91B1347A__INCLUDED_)
