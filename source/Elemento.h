///////////////////////////////////////////////////////////
//  Elemento.h
//  Implementation of the Class Elemento
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_)
#define EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_

#include "Orientacion.h"

typedef enum tipoElemento
{
	tSalidaPacman, tCasaFantasmas, tPowerup, tBonus
};

/**
 * Clase que representa cualquier objeto que puede estar situado en el mapa
 */
class Elemento
{

public:
	Elemento( tipoOrientacion tOrientacion = Norte);
	
	virtual ~Elemento();

	int getPosicion();
	
	virtual tipoElemento getTipo()const = 0;
	
	Orientacion getOrientacion()const;
	
	void setOrientacion( Orientacion orientacion);
	
	void SetPosicion(int newVal);
	
	virtual void renderizar();
	
	virtual bool operator==( tipoElemento tipo) const = 0;

private:
	
	Orientacion orientacion;
	int posicion; //es el id del vertice donde se encuentra el elemento
};
#endif // !defined(EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_)
