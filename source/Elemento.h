///////////////////////////////////////////////////////////
//  Elemento.h
//  Implementation of the Class Elemento
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_)
#define EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_

#include "Posicion.h"

/**
 * Clase que representa cualquier objeto que puede estar situado en el mapa
 */
class Elemento
{

public:
	Elemento();
	virtual ~Elemento();
	Posicion *m_Posicion;

	Posicion GetPosicion();
	virtual void renderizar();
	void SetPosicion(Posicion newVal);

private:
	Posicion posicion;

};
#endif // !defined(EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_)
