///////////////////////////////////////////////////////////
//  Mensaje.h
//  Implementation of the Class Mensaje
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_00555EAD_A002_4386_8DDE_5962FC3B0BA9__INCLUDED_)
#define EA_00555EAD_A002_4386_8DDE_5962FC3B0BA9__INCLUDED_

#include <string>

using std::string;

class Mensaje
{

public:
	Mensaje();
	virtual ~Mensaje();

	virtual string Serialize();

};
#endif // !defined(EA_00555EAD_A002_4386_8DDE_5962FC3B0BA9__INCLUDED_)
