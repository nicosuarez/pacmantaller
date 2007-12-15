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
	Personaje(Posicion& posicion);
	virtual ~Personaje();

	virtual int GetRol()const=0;
	
	Posicion *GetPosicion();
	
	virtual int GetVelocidad();
	
	void SetId(int id);
	
	void SetPosicion(Posicion& posicion);
	
	void SetVelocidad(int velocidad);
	
	virtual bool operator==( int tipo )const = 0;
	
	void chocoConPared(bool choco);
	
	bool chocoConPared();
	
	virtual double getRadio()const=0;
	
private:
	/**
	 * Identificador de personaje
	 */
	int idPersonaje;
	/**
	 * Posicion del personaje en el mapa
	 */
	Posicion posicion;
	/**
	 * Determina si el personaje a chocado con una pared.
	 */
	bool seChocoConPared;
	
	
protected:
	/**
	 * Velocidad del personaje
	 */
	int velocidad;

};
#endif // !defined(EA_93129EDB_E1C4_4602_9934_5696451996BE__INCLUDED_)
