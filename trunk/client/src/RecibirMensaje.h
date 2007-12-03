#ifndef RECIBIRMENSAJE_H_
#define RECIBIRMENSAJE_H_

#include <stdint.h>
#include <list>
#include "Socket.h"
#include "Mensaje.h"
#include "Modelo.h"
#include "SalidaPacMan.h"
#include "Bonus.h"
#include "PowerUp.h"
#include "CasaFantasmas.h"
#include "Pastilla.h"
#include "Thread.h"

class RecibirMensaje : public Thread
{
	Socket *socket;
	
	void recibirElementos( int cantElementos );
	
	void recibirMapa(  int ancho, int alto  );
	
	void actualizarJugador( PktPosiciones *posicion );
	
	void actualizarElemento( PktElementoStatus *elemento );
	
public:
	RecibirMensaje( Socket *socket );
	
	virtual ~RecibirMensaje();
	
	void main();
	
	void recibirMensaje();
	
	void recibirInit( PktCabecera *cabecera );
	
	void recibirStatus( PktCabecera *cabecera );
	
	/* Constructor de copia y operator= ocultos (para prevenir descuidos) */
	RecibirMensaje(const RecibirMensaje&);
	RecibirMensaje& operator=(const RecibirMensaje&);
};

#endif /*RECIBIRMENSAJE_H_*/
