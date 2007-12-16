///////////////////////////////////////////////////////////
//  Stop.h
//  Implementation of the Class Stop
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#if !defined(EA_72D732AB_1333_4cdf_975A_35F4250477B3__INCLUDED_)
#define EA_72D732AB_1333_4cdf_975A_35F4250477B3__INCLUDED_

#include "Mensaje.h"
#include "Modelo.h"

#define PACMAN_GANO 0
#define PACMAN_FUE_COMIDO 1
#define PACMAN_SE_DESCONECTO 2
#define JUGADORES_INSUFICIENTES 3
#define SERVER_TERMINADO 4

class Stop : public Mensaje
{
	int razon;
public:
	
	static const int STOP_TYPE = 3;

	Stop( int razon );
	
	virtual ~Stop();

	char* Serialize();

};
#endif // !defined(EA_72D732AB_1333_4cdf_975A_35F4250477B3__INCLUDED_)
