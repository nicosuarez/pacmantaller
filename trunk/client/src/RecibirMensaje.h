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
#include "Posicion.h"
#include "PacMan.h"
#include "Fantasma.h"
#include "Mapa.h"

class RecibirMensaje : public Thread
{
private:
	Socket *socket;
	
	void recibirElementos( int cantElementos );
	
	void recibirMapa(  int ancho, int alto  );
	
	void recibirPosiciones( int cantJugadores );
	
	void recibirElementosStatus( int cantElementos );
	
	int getIdVertice( int idArista);
	
	/* Constructor de copia y operator= ocultos (para prevenir descuidos) */
	RecibirMensaje(const RecibirMensaje&);
	RecibirMensaje& operator=(const RecibirMensaje&);
	
public:
	RecibirMensaje( Socket *socket );
	
	virtual ~RecibirMensaje();
	
	void main();
	
	void recibirMensaje();
	
	void recibirInit( PktCabecera *cabecera );
	
	void recibirStatus( PktCabecera *cabecera );
	
};

#endif /*RECIBIRMENSAJE_H_*/
