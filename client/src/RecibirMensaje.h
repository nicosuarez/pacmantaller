#ifndef RECIBIRMENSAJE_H_
#define RECIBIRMENSAJE_H_

#include <stdint.h>
#include <list>
#include <vector>
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
#include "Key.h"
#include "Coordenada.h"
#include "Vertice.h"
#include "ObjLoader.h"
#include "Model.h"
#include "LogResource.h"
#include "Camara.h"

//extern Camara camara;

class RecibirMensaje : public Thread
{
private:
	Socket *socket;
	
	std::vector<Vertice> vecVertices;
	
	void recibirElementos( int cantElementos );
	
	void recibirMapa(  int ancho, int alto  );
	
	void recibirPosiciones( int cantJugadores );
	
	void recibirElementosStatus( int cantElementos );
	
	int getIdVertice( int idArista, int direccion, int anchoMapa );
	
	void recibirInit( PktCabecera *cabecera );
	
	void recibirStatus( PktCabecera *cabecera );
	
	void agregarElemento( PktElemento *pktElemento );
	
	void crearVerticesMapa();
	
	Coordenada buscarCoordenada(int idVert); 
	
	/* Constructor de copia y operator= ocultos (para prevenir descuidos) */
	RecibirMensaje(const RecibirMensaje&);
	RecibirMensaje& operator=(const RecibirMensaje&);
	

	int calcularEje(int idVertice,int idArista,int ancho);
	float calcularIncremento(int posicionArista);
	void agregarPersonaje(int idJugador, Posicion posicion);

	
public:
	RecibirMensaje( Socket *socket );
	
	virtual ~RecibirMensaje();
	
	void main();
	
	void recibirMensaje();
		
};

#endif /*RECIBIRMENSAJE_H_*/
