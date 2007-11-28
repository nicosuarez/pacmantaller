
///////////////////////////////////////////////////////////
//  Init.h
//  Implementation of the Class Init
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_6FA4E41D_A508_4e6c_973A_6300F384D81B__INCLUDED_)
#define EA_6FA4E41D_A508_4e6c_973A_6300F384D81B__INCLUDED_

#ifdef __GNUC__
#define PACKED __attribute__((__packed__))
#else
#error Debe compilar con GCC
#endif

#include <stdint.h>
#include "Mensaje.h"
#include "AppSettings.h"
#define TIPO_INIT 0

typedef struct PktInit
{
	//cabecera
	uint8_t version: 2;
	uint8_t tipo: 3;
	uint8_t rol: 1;
	uint8_t padding: 2;
	//cuerpo
	uint8_t ancho;
	uint8_t alto;
};

class Init : public Mensaje
{
private:
	int rol;

public:
	
	Init( int rol);

	virtual ~Init();
	
	int getTipo();

	char* Serialize();

}__attribute__((__packed__));


#endif // !defined(EA_6FA4E41D_A508_4e6c_973A_6300F384D81B__INCLUDED_)
