///////////////////////////////////////////////////////////
//  Mensaje.h
//  Implementation of the Class Mensaje
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_00555EAD_A002_4386_8DDE_5962FC3B0BA9__INCLUDED_)
#define EA_00555EAD_A002_4386_8DDE_5962FC3B0BA9__INCLUDED_

#include <string>
#include "Paquetes.h"

class Mensaje
{
	
protected:
	int sizePkt;
	
public:
	
	static const int INIT_TYPE = 0;
	static const int START_TYPE = 1;
	static const int STATUS_TYPE = 2;
	static const int STOP_TYPE = 3;
	static const int QUIT_TYPE = 4;
	
	Mensaje();
	
	virtual ~Mensaje();
	 
	virtual char* Serialize()=0;

	int getSize()const;
};
#endif // !defined(EA_00555EAD_A002_4386_8DDE_5962FC3B0BA9__INCLUDED_)
