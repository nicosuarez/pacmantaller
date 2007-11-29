///////////////////////////////////////////////////////////
//  Mensaje.h
//  Implementation of the Class Mensaje
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_00555EAD_A002_4386_8DDE_5962FC3B0BA9__INCLUDED_)
#define EA_00555EAD_A002_4386_8DDE_5962FC3B0BA9__INCLUDED_

#ifdef __GNUC__
#define PACKED __attribute__((__packed__))
#else
#error Debe compilar con GCC
#endif

#include <string>
#include "Modelo.h"

typedef struct PktCabecera
{
	uint8_t version: 2;
	uint8_t tipo: 3;
	uint8_t aux: 3;
}__attribute__((__packed__));

class Mensaje
{

public:
	Mensaje();
	
	virtual ~Mensaje();
	
	virtual int getTipo()=0;
 
	virtual char* Serialize()=0;

};
#endif // !defined(EA_00555EAD_A002_4386_8DDE_5962FC3B0BA9__INCLUDED_)
