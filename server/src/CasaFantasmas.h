///////////////////////////////////////////////////////////
//  CasaFantasmas.h
//  Implementation of the Class CasaFantasmas
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_8B343B63_2435_4646_A883_375D52FA746A__INCLUDED_)
#define EA_8B343B63_2435_4646_A883_375D52FA746A__INCLUDED_

#include "Elemento.h"
#include  <vector>

typedef std::vector<int> tVecVerticeId;

/**
 * Clase que modela la casa de los fantasmas lugar de inicio de los mismos, cuando
 * un fantasmas es comido por el pacman en estado powerup, el fantasma se vuelve
 * invisible y no afecta el juego hasta que no pase por la casa.
 */
class CasaFantasmas : public Elemento
{
private:
	tVecVerticeId vertices;

public:
	CasaFantasmas( int posicion = -1, Orientacion orientacion=Norte);
	
	virtual ~CasaFantasmas();
	
	tipoElemento getTipo()const;

	void renderizar();
	
	bool operator==( tipoElemento tipo) const;
	
	//Vector con los id de los vertice que compone la casa, menos la entrada
	tVecVerticeId* getVerticesId();
	
	void setVerticesId(tVecVerticeId& vertices);

};
#endif // !defined(EA_8B343B63_2435_4646_A883_375D52FA746A__INCLUDED_)
