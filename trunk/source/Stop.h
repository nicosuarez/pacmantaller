///////////////////////////////////////////////////////////
//  Stop.h
//  Implementation of the Class Stop
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#if !defined(EA_72D732AB_1333_4cdf_975A_35F4250477B3__INCLUDED_)
#define EA_72D732AB_1333_4cdf_975A_35F4250477B3__INCLUDED_

#include "string.h"
#include "Mensaje.h"

class Stop : public Mensaje
{

public:
	Stop();
	virtual ~Stop();

	string Serialize();

};
#endif // !defined(EA_72D732AB_1333_4cdf_975A_35F4250477B3__INCLUDED_)
