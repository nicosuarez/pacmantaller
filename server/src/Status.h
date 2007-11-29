///////////////////////////////////////////////////////////
//  Status.h
//  Implementation of the Class Status
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#if !defined(EA_CCA19AC9_3E92_4a3c_8EFC_16B615225CE3__INCLUDED_)
#define EA_CCA19AC9_3E92_4a3c_8EFC_16B615225CE3__INCLUDED_

#include "Mensaje.h"
#include "AppSettings.h"
#include "Modelo.h"
#include "Personaje.h"
#include "Posicion.h"

#define TIPO_STATUS 2

class Status : public Mensaje
{

public:
	Status();
	
	virtual ~Status();

	int getTipo();
	
	char* Serialize();

};
#endif // !defined(EA_CCA19AC9_3E92_4a3c_8EFC_16B615225CE3__INCLUDED_)