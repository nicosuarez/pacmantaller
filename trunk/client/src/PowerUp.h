///////////////////////////////////////////////////////////
//  PowerUp.h
//  Implementation of the Class PowerUp
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_36BDC085_0509_46c5_AB9B_B4CF19D4F9EE__INCLUDED_)
#define EA_36BDC085_0509_46c5_AB9B_B4CF19D4F9EE__INCLUDED_

#include "Elemento.h"

/**
 * Clase que modela la pastilla powerUp
 * 
 */
class PowerUp : public Elemento
{

public:
	PowerUp( int posicion, Orientacion orientacion= Norte );
	
	PowerUp( int posicion, Coordenada coord, Orientacion orientacion = Norte );
	
	virtual ~PowerUp();
	
	tipoElemento getTipo()const;

	void renderizar();
	
	bool operator==( tipoElemento tipo) const;

};
#endif // !defined(EA_36BDC085_0509_46c5_AB9B_B4CF19D4F9EE__INCLUDED_)
