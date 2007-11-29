///////////////////////////////////////////////////////////
//  Operacion.h
//  Implementation of the Class Operacion
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#if !defined(EA_9A3DFB1D_40D2_4167_894A_F5464BCE129F__INCLUDED_)
#define EA_9A3DFB1D_40D2_4167_894A_F5464BCE129F__INCLUDED_

#include "Modelo.h"

class Modelo;

/**
 * Clase Abstracta que permite implementar mediante el polimorfismo ejecutar cada
 * operacion hija.
 */
class Operacion
{

public:
	Operacion();
	virtual ~Operacion();

	virtual bool ejecutar(Modelo* modelo);

protected:
	virtual void internalProcess();
	virtual bool validarOperacion();

};
#endif // !defined(EA_9A3DFB1D_40D2_4167_894A_F5464BCE129F__INCLUDED_)
