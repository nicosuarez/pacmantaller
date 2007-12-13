#ifndef MODELO_H_
#define MODELO_H_
#include <iostream>
#include <list>
#include "Elemento.h"
#include "Personaje.h"
#include "Mapa.h"
#include "EnviarMensaje.h"
//#include "Thread.h"

class EnviarMensaje;

class Modelo
{
private:
	static Modelo* pModelo;
	int id;
	int puntuacion;
	bool finalizoJuego;
	bool finalizoNivel;
	Mapa *mapa;
	std::list<Elemento*> *elementos;
	std::list<Personaje*> personajes;
	EnviarMensaje *enviarMensaje;
	Modelo();

    Evento recibiMensajeInitEvent;
    
public:
	Evento& getRecibiMensajeInitEvent();
	
	virtual ~Modelo();
	
	static Modelo* getInstance();
	
	void setid( int newid );
	
	void setPuntuacion( int newPuntuacion );
	
	void setFinalizoJuego( bool finalizo );
	
	void setFinalizoNivel( bool finalizo );
	
	void setMapa( Mapa *mapa );
	
	void setElementos( std::list<Elemento*> *elementos );
	
	void setEnviarMensaje( EnviarMensaje *enviarMensaje );
	
	EnviarMensaje* getEnviarMensaje();
	
	int getid()const;
	
	int getPuntuacion()const;
	
	bool getFinalizoJuego()const;
	
	bool getFinalizoNivel()const;
	
	Mapa* getMapa();
	
	std::list<Elemento*>* getElementos();
	
	std::list<Personaje*>* getPersonajes();
	
	Personaje* getPersonaje( int id );
	
	void eliminarElementos();
	
	void eliminarPersonajes();
};

#endif /*MODELO_H_*/
