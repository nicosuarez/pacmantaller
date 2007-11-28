///////////////////////////////////////////////////////////
//  Dispatcher.h
//  Implementation of the Class Dispatcher
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_15129548_CA1C_4143_A7FB_A6812DF62A1F__INCLUDED_)
#define EA_15129548_CA1C_4143_A7FB_A6812DF62A1F__INCLUDED_

#include "Evento.h"
#include "Mensaje.h"
#include "Mutex.h"
#include "ConnectionManager.h"
#include <queue>

typedef  std::queue<Mensaje*> tQueueMensajes;

/**
 * Clase engarda de despachar los mensajes a todos los jugadores..
 */
class Dispatcher
{
private:
    tQueueMensajes mensajes;
    Evento recibiMensajeEvent;
    Mutex * m_dispacher;

    /* Metodos */
    tListJugadores& getJugadoresList();
    void main();
public:
	Dispatcher();

	/*Estos mensajes se acolan para que luego el hilo del 
	* despachador vaya iterando sobre todas las conexiones activas enviando a 
	* través del socket correspondiente los mensajes a cada cliente.
	*/
	void enviarMensaje(Mensaje* mensaje);
	
	/* Getters y Setters */
	Evento& getRecibiMensajeEvent();

    /* Contructores y Destructores */
    Dispatcher(Mutex* m_dispacher);
};
#endif // !defined(EA_15129548_CA1C_4143_A7FB_A6812DF62A1F__INCLUDED_)
