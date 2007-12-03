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

typedef struct PktCabecera
{
	uint8_t version: 2;
	uint8_t tipo: 3;
	uint8_t aux: 3;
}__attribute__((__packed__));

typedef struct PktElemento
{
	uint8_t tipo: 6;
	uint8_t orientacion: 2;
	uint16_t posicion;
}__attribute__((__packed__));

typedef struct PktPosiciones
{
	uint16_t id;
	uint32_t arista: 17;
	uint8_t posicion: 6;
	uint8_t direccion: 1;
}__attribute__((__packed__));

typedef struct PktElementoStatus
{
	uint8_t tipo: 4;
	uint8_t orientacion: 2;
	uint8_t estado: 2;
	uint16_t posicion;
}__attribute__((__packed__));

class Mensaje
{

public:
	
	static const int INIT_TYPE = 0;
	static const int START_TYPE = 1;
	static const int STATUS_TYPE = 2;
	static const int STOP_TYPE = 3;
	static const int QUIT_TYPE = 4;
	
	Mensaje();
	
	virtual ~Mensaje();
	 
	virtual char* Serialize()=0;

};
#endif // !defined(EA_00555EAD_A002_4386_8DDE_5962FC3B0BA9__INCLUDED_)
