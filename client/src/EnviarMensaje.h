#ifndef ENVIARMENSAJE_H_
#define ENVIARMENSAJE_H_

#include "Thread.h"
#include "Socket.h"
#include "Mutex.h"
#include "Evento.h"
#include "Modelo.h"
#include "Mensaje.h"
#include <queue>

typedef std::queue<Mensaje*> tColaMensajes;
class EnviarMensaje: public Thread
{
	Socket *socket;
	tColaMensajes mensajes;
	Mutex m_mensajes;
	Evento evento;
	
public:
	//Constructor
	EnviarMensaje( Socket *socket );
	
	//Destructor
	virtual ~EnviarMensaje();
	
	void enviarMensaje( Mensaje *mensaje );
	
	void main();
};

#endif /*ENVIARMENSAJE_H_*/
