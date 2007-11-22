///////////////////////////////////////////////////////////
//  Fantasma.h
//  Implementation of the Class Fantasma
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_E4309321_8E59_4003_BC67_09BA7FB5090B__INCLUDED_)
#define EA_E4309321_8E59_4003_BC67_09BA7FB5090B__INCLUDED_

#include "Personaje.h"

/**
 * Clase que modela el personaje Fantasma
 */
class Fantasma : public Personaje
{

public:
	Fantasma();
	virtual ~Fantasma();

	virtual int GetVelocidad();
	bool IsVisible();
	void SetVisible(bool visible);

private:
	/**
	 * Velocidad inicial constante del fantasma
	 */
	static const int velocidadInicial=0;
	/**
	 * Determina si el fantasma esta en estado invisible que ocurre cuando un pacman
	 * en estado powerUp como el fantasma. Cuando el mismo se encuentra invisible no
	 * puede volver entrar en juego hasta que no haya pasado por la casa.
	 */
	bool visible;

};
#endif // !defined(EA_E4309321_8E59_4003_BC67_09BA7FB5090B__INCLUDED_)
