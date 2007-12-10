///////////////////////////////////////////////////////////
//  Dispatcher.h
//  Implementation of the Class Dispatcher
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_15129548_CA1C_4143_A7FB_A6812DF62A1F__INCLUDED_)
#define EA_15129548_CA1C_4143_A7FB_A6812DF62A1F__INCLUDED_

#include <queue>
#include <list>
#include "Thread.h"
#include "Evento.h"
#include "Mutex.h"
#include "Mensaje.h"
#include "Jugador.h"

typedef  std::queue<Mensaje*> tQueueMensajes;
typedef std::list<Jugador*> listJugadores;


/**
 * Clase encargada de despachar los mensajes a todos los jugadores..
 */
class Dispatcher: public Thread
{
private:
	//Cola de mensajes a envia
	tQueueMensajes mensajes;
   
	//Lista de Jugadores a los que se les envia los mensajes
    listJugadores *jugadores;

    Evento recibiMensajeEvent;
    
    //booleano para saber si finalizo el juego
    bool *terminoJuego;
    
    //Mutex del modelo que protege la lista de jugadores
    Mutex *m_jugadores;
    
    //Mutex que protege la cola de mensajes
    Mutex m_mensajes; 

    /* Metodos */
 
    //Retorna el jugador con id=idJugador
    Jugador* getJugador(int idJugador);
    
    //Desacola los mensajes de la cola y los envia a los clientes
    void main();
    
	// Envia un mensaje a todos los jugadores
	void enviarBroadCast(Mensaje* msg);
	
	//Envia un mensaje a un jugador en particular.
	void enviarMensajeParticular(Mensaje* msg);
public:
	
	/*Estos mensajes se acolan para que luego el hilo del 
	* despachador vaya iterando sobre todas las conexiones activas enviando a 
	* través del socket correspondiente los mensajes a cada cliente.
	*/
	void enviarMensaje( Mensaje* mensaje, int idJugador = BROADCAST );
	
	/* Getters y Setters */
	Evento& getRecibiMensajeEvent();

    /* Contructores y Destructores */
    Dispatcher( listJugadores *jugadores, bool *terminoJuego, Mutex *m_jugadores );
    
    ~Dispatcher();
};
#endif // !defined(EA_15129548_CA1C_4143_A7FB_A6812DF62A1F__INCLUDED_)
