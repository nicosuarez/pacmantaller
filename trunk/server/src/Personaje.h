///////////////////////////////////////////////////////////
//  Personaje.h
//  Implementation of the Class Personaje
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_93129EDB_E1C4_4602_9934_5696451996BE__INCLUDED_)
#define EA_93129EDB_E1C4_4602_9934_5696451996BE__INCLUDED_

#include "Posicion.h"

/**
 * Clase que modela los personajes del juego
 */
class Personaje
{

public:
	Personaje();
	virtual ~Personaje();
	Posicion *m_Posicion;

	int GetId();
	Posicion *GetPosicion();
	virtual int GetVelocidad();
	void SetId(int newVal);
	void SetPosicion(Posicion newVal);
	void SetVelocidad(int newVal);

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

};
#endif // !defined(EA_93129EDB_E1C4_4602_9934_5696451996BE__INCLUDED_)
