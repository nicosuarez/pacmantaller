#ifndef CERRARSERVIDOROP_H_
#define CERRARSERVIDOROP_H_

#include "Operacion.h"
#include "Modelo.h"
#include "Quit.h"
#include "ConnectionManager.h"
#include "Dispatcher.h"

class CerrarServidorOp : public Operacion
{
public:
	CerrarServidorOp();
	bool ejecutar();
	
protected:
	void internalProcess(){};
	bool validarOperacion(){return false;};
};

#endif /*CERRARSERVIDOROP_H_*/
