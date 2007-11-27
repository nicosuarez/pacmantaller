///////////////////////////////////////////////////////////
//  Start.h
//  Implementation of the Class Start
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#if !defined(EA_1FD97E6C_758A_441c_BE3E_92C7917F7A84__INCLUDED_)
#define EA_1FD97E6C_758A_441c_BE3E_92C7917F7A84__INCLUDED_
#include "AppSettings.h"
#include "Mensaje.h"
#define TIPO_START 1

typedef struct PktStart: PktCabecera
{
	uint16_t id;
};

class Start : public Mensaje
{
	int id;

public:
	Start( int id );
	
	virtual ~Start();

	int getTipo();
	
	char* Serialize();

};
#endif // !defined(EA_1FD97E6C_758A_441c_BE3E_92C7917F7A84__INCLUDED_)
