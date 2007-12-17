///////////////////////////////////////////////////////////
//  PacMan.h
//  Implementation of the Class PacMan
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#if !defined(EA_B035D27E_31A5_4b0f_B082_3F7AF1A2C886__INCLUDED_)
#define EA_B035D27E_31A5_4b0f_B082_3F7AF1A2C886__INCLUDED_

#include "Personaje.h"
#include "Modelo.h"
#include "Timer.h"


/**
 * Clase que modela el PacMan
 */
class PacMan : public Personaje
{

public:
	PacMan();
	PacMan(Posicion& posicion);
	virtual ~PacMan();
	
	
	static const int PACMAN_TYPE = 0;
	Timer mantenerEstado;
	int GetRol()const;
	int GetVelocidad();
	double getRadio()const;
	bool IsPowerUp();
	void SetPowerUp();
	bool operator==( int tipo )const;
	int getPuntaje(){return puntaje;};
	void incPuntaje(int puntaje){this->puntaje += puntaje;};
	void comer();
	/**
	 * Valor constante de la velocidad inicial del pacman
	 */
	static const int velocidadInicial=16;
	
private:
	/**
	 * Puntaje acumulado del pacman
	 */
	int puntaje;
	/**
	 * Determina si el pacman se encuentra en el estado powerUp
	 */
	bool isPowerUp;
	/**
	 * Radio constante del pacman
	 */
	static const double radio = 0.5;
	
	/**
	 * Valor constante de tiempo en estado de powerUp (ms)
	 */
	static const int tiempoPowerUp=10000;

};
#endif // !defined(EA_B035D27E_31A5_4b0f_B082_3F7AF1A2C886__INCLUDED_)
