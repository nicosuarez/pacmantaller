///////////////////////////////////////////////////////////
//  Start.h
//  Implementation of the Class Start
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#if !defined(EA_1FD97E6C_758A_441c_BE3E_92C7917F7A84__INCLUDED_)
#define EA_1FD97E6C_758A_441c_BE3E_92C7917F7A84__INCLUDED_
#include "AppSettings.h"
#include "Mensaje.h"

typedef struct PktStart: PktCabecera
{
	uint16_t id;
};

class Start : public Mensaje
{
	int id;

public:
	
	static const int START_TYPE = 1;
	
	Start( int id );
	
	virtual ~Start();
	
	char* Serialize();

};
#endif // !defined(EA_1FD97E6C_758A_441c_BE3E_92C7917F7A84__INCLUDED_)
