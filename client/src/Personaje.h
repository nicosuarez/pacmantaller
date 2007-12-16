///////////////////////////////////////////////////////////
//  Personaje.h
//  Implementation of the Class Personaje
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_93129EDB_E1C4_4602_9934_5696451996BE__INCLUDED_)
#define EA_93129EDB_E1C4_4602_9934_5696451996BE__INCLUDED_

#include <GL/glut.h>
#include "Posicion.h"
#include "Coordenada.h"
#include "Model.h"


#define P_ESCALAX 0.14f
#define	P_ESCALAY 0.14f
#define	P_ESCALAZ 0.14f
#define F_ESCALAX 0.050f
#define	F_ESCALAY 0.060f
#define	F_ESCALAZ 0.050f

/**
 * Clase que modela los personajes del juego
 */
class Personaje
{

public:
	Personaje();
	Personaje(Posicion& posicion);
	
	//****************//
		
	virtual ~Personaje();

	virtual int GetRol()const=0;
	Posicion *GetPosicion();
	virtual int GetVelocidad();
	int GetId()const;
	
	void SetId(int id);
	void SetPosicion(Posicion posicion);
	void SetVelocidad(int velocidad);
	void SetModel(Model* model);
	
	void SetCoord(Coordenada coord);
	void SetRotacion(Coordenada rotacion);	
	virtual bool operator==( int tipo )const = 0;
	
	//***********************//
	virtual void renderizar();
	
	
private:
	/**
	 * Identificador de personaje
	 */
	int idPersonaje;
	/**
	 * Posicion del personaje en el mapa
	 */
	Posicion posicion;
	
protected:
	/**
	 * Velocidad del personaje
	 */
	int velocidad;
			
	Coordenada coord;
	Coordenada rotacion;	
	
	Model *model;

};

#endif // !defined(EA_93129EDB_E1C4_4602_9934_5696451996BE__INCLUDED_)

