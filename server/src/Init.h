
///////////////////////////////////////////////////////////
//  Init.h
//  Implementation of the Class Init
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_6FA4E41D_A508_4e6c_973A_6300F384D81B__INCLUDED_)
#define EA_6FA4E41D_A508_4e6c_973A_6300F384D81B__INCLUDED_

#include "Mensaje.h"
#include "Modelo.h"

class Init : public Mensaje
{
private:
	int rol;

public:
	
	static const int INIT_TYPE = 0;
	
	Init( int rol);

	virtual ~Init();
	
	char* Serialize();

};

#endif // !defined(EA_6FA4E41D_A508_4e6c_973A_6300F384D81B__INCLUDED_)
