///////////////////////////////////////////////////////////
//  Status.h
//  Implementation of the Class Status
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#if !defined(EA_CCA19AC9_3E92_4a3c_8EFC_16B615225CE3__INCLUDED_)
#define EA_CCA19AC9_3E92_4a3c_8EFC_16B615225CE3__INCLUDED_

#include "Mensaje.h"
#include "AppSettings.h"
#include "Modelo.h"
#include "Personaje.h"
#include "Posicion.h"

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

class Status : public Mensaje
{

	tListaElemento *elementos;
public:
	
	static const int STATUS_TYPE = 2;
	
	Status( tListaElemento *elementos);
	
	virtual ~Status();
	
	char* Serialize();

};
#endif // !defined(EA_CCA19AC9_3E92_4a3c_8EFC_16B615225CE3__INCLUDED_)
