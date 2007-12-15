#ifndef CERRARSERVIDOROP_H_
#define CERRARSERVIDOROP_H_

#include "Operacion.h"
#include "Modelo.h"
#include "Quit.h"
#include "ConnectionManager.h"

class CerrarServidorOp : public Operacion
{
public:
	CerrarServidorOp();
	bool ejecutar();

};

#endif /*CERRARSERVIDOROP_H_*/
