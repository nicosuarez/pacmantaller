///////////////////////////////////////////////////////////
//  PacMan.h
//  Implementation of the Class PacMan
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#if !defined(EA_B035D27E_31A5_4b0f_B082_3F7AF1A2C886__INCLUDED_)
#define EA_B035D27E_31A5_4b0f_B082_3F7AF1A2C886__INCLUDED_

#include "Personaje.h"

/**
 * Clase que modela el PacMan
 */
class PacMan : public Personaje
{

public:
	PacMan();
	virtual ~PacMan();

	
	static const int PACMAN_TYPE = 0;
	int GetRol()const;
	int GetVelocidad();
	bool IsPowerUp();
	void SetPowerUp(bool newVal);
	bool operator==( int tipo )const;

private:
	/**
	 * Determina si el pacman se encuentra en el estado powerUp
	 */
	bool isPowerUp;
	/**
	 * Valor constante de la velocidad inicial del pacman
	 */
	static const int velocidadInicial=0;

};
#endif // !defined(EA_B035D27E_31A5_4b0f_B082_3F7AF1A2C886__INCLUDED_)
