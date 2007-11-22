///////////////////////////////////////////////////////////
//  Start.h
//  Implementation of the Class Start
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#if !defined(EA_1FD97E6C_758A_441c_BE3E_92C7917F7A84__INCLUDED_)
#define EA_1FD97E6C_758A_441c_BE3E_92C7917F7A84__INCLUDED_

#include "string.h"
#include "Mensaje.h"

class Start : public Mensaje
{

public:
	Start();
	virtual ~Start();

	string Serialize();

};
#endif // !defined(EA_1FD97E6C_758A_441c_BE3E_92C7917F7A84__INCLUDED_)
