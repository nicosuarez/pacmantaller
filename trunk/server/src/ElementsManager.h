///////////////////////////////////////////////////////////
//  ElementsManager.h
//  Implementation of the Class ElementsManager
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_BC2323FF_9B32_4b02_BDD4_D4E228A2C27D__INCLUDED_)
#define EA_BC2323FF_9B32_4b02_BDD4_D4E228A2C27D__INCLUDED_

#include "Operacion.h"
#include <iostream>
/**
 * Clase encargada de generar las operaciones que agregan en el mapa los bonus y
 * powersUp
 */
class ElementsManager
{

public:
	ElementsManager();
	virtual ~ElementsManager();

	Operacion* GetAgregarBonusOp();
	Operacion* GetAgregarPowerUpOp();

};
#endif // !defined(EA_BC2323FF_9B32_4b02_BDD4_D4E228A2C27D__INCLUDED_)
