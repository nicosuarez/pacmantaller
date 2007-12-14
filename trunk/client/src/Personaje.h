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


/**
 * Clase que modela los personajes del juego
 */
class Personaje
{

public:
	Personaje();
	Personaje(Posicion& posicion);
	
	//****************//
	Personaje(Posicion& posicion, Coordenada cTranslate);
	
	virtual ~Personaje();

	virtual int GetRol()const=0;
	Posicion *GetPosicion();
	virtual int GetVelocidad();
	int GetId()const;
	void SetId(int id);
	void SetPosicion(Posicion posicion);
	void SetVelocidad(int velocidad);
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
	
	//***************//
	Coordenada cTranslate;
	Model *model;
	/*Coordenada cTranslate;//Translate
	Coordenada cRotate;//Rotate
	Coordenada cScale;//Scale*/

};
#endif // !defined(EA_93129EDB_E1C4_4602_9934_5696451996BE__INCLUDED_)
