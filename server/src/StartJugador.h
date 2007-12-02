///////////////////////////////////////////////////////////
//  StartJugador.h
//  Implementation of the Class StartJugador
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_F88EAA8B_43FD_4d3a_825C_387F3C6CC318__INCLUDED_)
#define EA_F88EAA8B_43FD_4d3a_825C_387F3C6CC318__INCLUDED_

#include "Thread.h"
#include "Evento.h"
#include "Play.h"
#include <string>
#include <queue>

class Play;

typedef bool* pBool;
typedef std::queue<Play*> tQueueStart;
using std::string;


/**
 * Hilo que se encarga agregar un jugador al juego, dando tiempo para que 
 * muestre el mapa. 
 */
class StartJugador: public Thread
{

public:
	void esperarRecibirStart();
	Play* desacolar();
	Play* getStart();
	void agregarStart(Play* play);	
	void main();
	static StartJugador* getInstance(); 

	/* Eventos */
	Evento& getRecibiStartEvent(){return this->recibiStartEvent;};
	
protected:
	StartJugador();
	StartJugador(const StartJugador&);
	StartJugador& operator= (const StartJugador&);
	
private:
	static StartJugador* pStartJugador;
	/**
	 * Evento que determina si recibio una operacion
	 */
	Evento recibiStartEvent;
	/**
	 * Lista de jugadores que inicial el juego.
	 */
	tQueueStart startPlayers;

};
#endif // !defined(EA_F88EAA8B_43FD_4d3a_825C_387F3C6CC318__INCLUDED_)
