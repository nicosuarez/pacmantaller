///////////////////////////////////////////////////////////
//  Stop.h
//  Implementation of the Class Stop
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#if !defined(EA_72D732AB_1333_4cdf_975A_35F4250477B3__INCLUDED_)
#define EA_72D732AB_1333_4cdf_975A_35F4250477B3__INCLUDED_

#include "Mensaje.h"
#include "Modelo.h"
#define TIPO_STOP 3

typedef struct PktStop: PktCabecera
{
	uint32_t puntuacion;
};


class Stop : public Mensaje
{
	int razon;
public:
	Stop( int razon );
	
	virtual ~Stop();
	
	int getTipo();

	char* Serialize();

};
#endif // !defined(EA_72D732AB_1333_4cdf_975A_35F4250477B3__INCLUDED_)
