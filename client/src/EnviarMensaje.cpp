#include "EnviarMensaje.h"

EnviarMensaje::EnviarMensaje( Socket *socket)
{
	this->socket = socket;
}

EnviarMensaje::~EnviarMensaje()
{
}

void EnviarMensaje::enviarMensaje( Mensaje *mensaje )
{
	m_mensajes.lock();
	mensajes.push( mensaje );
	m_mensajes.unlock();
	evento.activar();
}

void EnviarMensaje::main()
{
	Modelo *modelo = Modelo::getInstance();
	while( !modelo->getFinalizoJuego() )
	{
		//Si no hay mensajes, espera a recibir
		if( mensajes.empty() )
			evento.esperar();
		m_mensajes.lock();
		Mensaje* mensaje = mensajes.front();
		mensajes.pop();
		m_mensajes.unlock();
		char *buffer = mensaje->Serialize();
		socket->enviar( buffer, mensaje->getSize() );
		delete []buffer;
	}
}
