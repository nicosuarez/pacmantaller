#ifndef MODELO_H_
#define MODELO_H_
#include <iostream>
#include <list>
#include "Personaje.h"
#include "Mapa.h"
#include "EnviarMensaje.h"
#include "Pastilla.h"
#include "Bonus.h"
#include "PowerUp.h"
#include "CasaFantasmas.h"
#include "SalidaPacMan.h"
#include "Mutex.h"
#include "Camara.h"
#include "LogResource.h"
#include "ObjLoader.h"

class EnviarMensaje;
typedef std::list<Pastilla*> tListPastilla;
typedef std::list<Bonus*> tListBonus;
typedef std::list<PowerUp*> tListPower;
typedef std::list<Personaje*> tListPersonaje;
//**********************
typedef std::list<int> tListAristaPortal;
//*********************

class Modelo
{
private:
	static Modelo* pModelo;
	int id;
	int puntuacion;
	bool finalizoJuego;
	bool finalizoNivel;
	Mapa *mapa;
	tListPastilla pastillas;
	tListBonus bonus;
	tListPower powers;
	tListPersonaje personajes;
	CasaFantasmas* casaFantasmas;
	SalidaPacMan* salidaPacMan;
	EnviarMensaje *enviarMensaje;
    Evento recibiMensajeInitEvent;
    Camara camara;
    Mutex m_pastillas;
	Mutex m_bonus;
	Mutex m_powers;
	Mutex m_personajes;
	Mutex m_mapa;
	Modelo();
	tListAristaPortal aristasPortal;
	
	/*
	Model* modelPacman;
	Model* modelFantasma;*/
	
public:
	Evento& getRecibiMensajeInitEvent();
	
	virtual ~Modelo();
	
	static Modelo* getInstance();
	
	void setid( int newid );
	
	void setPuntuacion( int newPuntuacion );
	
	void setFinalizoJuego( bool finalizo );
	
	void setFinalizoNivel( bool finalizo );
	
	void setMapa( Mapa *mapa );
	
	void setCasaFantasmas( CasaFantasmas* casaFantasmas );
	
	void setSalidaPacMan( SalidaPacMan* salidaPacman );
	
	void setEnviarMensaje( EnviarMensaje *enviarMensaje );
	
	EnviarMensaje* getEnviarMensaje();
	
	int getid()const;
	
	int getPuntuacion()const;
	
	bool getFinalizoJuego()const;
	
	bool getFinalizoNivel()const;
	
	Mapa* getMapa();
		
	//Devuelve el elemento que esta ubicado en la posicion
	Elemento* getElemento( tipoElemento tipo, int posicion );
	
	//Devuelve una referencia a la lista de pastillas
	tListPastilla& getPastillas();
	
	//Devuelve una referencia a la lista de Bonus
	tListBonus& getBonus();
	
	//Devuelve una referencia a la lista de PowerUps
	tListPower& getPowers();
	
	//Devuelve una referencia a la lista de personajes
	tListPersonaje& getPersonajes();
	
	Personaje* getPersonaje( int id );
	
	CasaFantasmas* getCasaFantasmas();
	
	SalidaPacMan* getSalidaPacMan();
	
	Mutex& getMutexPastillas();
	
	Mutex& getMutexBonus();
	
	Mutex& getMutexPowers();
	
	Mutex& getMutexPersonajes();
	
	Mutex& getMutexMapa();
	
	//void quitarBonus( int idPosicion );
	
	void eliminarPersonajes();
	
	void eliminarPastillas();
	
	void eliminarBonus();
	
	void eliminarPowers();
	
	Camara& getCamara(); 
	
	tListAristaPortal& getAristasPortal();
	    
	/*Model* getModelPacman();
		Model* getModelFantasma();*/
};

#endif /*MODELO_H_*/
