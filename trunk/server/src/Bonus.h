///////////////////////////////////////////////////////////
//  Bonus.h
//  Implementation of the Class Bonus
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_FA7D0A8D_70C6_47c2_A215_B4D860C19A44__INCLUDED_)
#define EA_FA7D0A8D_70C6_47c2_A215_B4D860C19A44__INCLUDED_

#include "Elemento.h"

/**
 * Clase que modela el bonus
 */
class Bonus : public Elemento
{

public:
	Bonus( int posicion=-1, Orientacion orientacion=Norte );
	
	virtual ~Bonus();
	
	tipoElemento getTipo()const;

	virtual void renderizar();
	
	bool operator==( tipoElemento tipo) const;
	
	int getPuntaje(){return  puntaje;};
	
	static const int puntaje=50;

};
#endif // !defined(EA_FA7D0A8D_70C6_47c2_A215_B4D860C19A44__INCLUDED_)
