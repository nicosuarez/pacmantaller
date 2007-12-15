#ifndef CAMBIARDENIVELOP_H_
#define CAMBIARDENIVELOP_H_

#include "Operacion.h"
#include "Modelo.h"

class CambiarDeNivelOp : public Operacion
{
public:
	//Constructor
	CambiarDeNivelOp();
	
	//Destructor
	virtual ~CambiarDeNivelOp();
	
	//Finaliza el nivel para poder inciar uno nuevo.
	bool ejecutar();
};

#endif /*CAMBIARDENIVELOP_H_*/
