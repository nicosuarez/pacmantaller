///////////////////////////////////////////////////////////
//  Init.h
//  Implementation of the Class Init
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_6FA4E41D_A508_4e6c_973A_6300F384D81B__INCLUDED_)
#define EA_6FA4E41D_A508_4e6c_973A_6300F384D81B__INCLUDED_

#include "Mensaje.h"

class Init : public Mensaje
{

public:
	Init();
	virtual ~Init();

	virtual string Serialize();

};
#endif // !defined(EA_6FA4E41D_A508_4e6c_973A_6300F384D81B__INCLUDED_)
