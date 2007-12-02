#ifndef CERRARSERVIDOROP_H_
#define CERRARSERVIDOROP_H_

#include "Operacion.h"

class CerrarServidorOp : public Operacion
{
public:
	CerrarServidorOp();
	bool ejecutar(Modelo* modelo);
	
protected:
	void internalProcess(){};
	bool validarOperacion(){return false;};
};

#endif /*CERRARSERVIDOROP_H_*/
