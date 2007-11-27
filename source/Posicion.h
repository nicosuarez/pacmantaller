///////////////////////////////////////////////////////////
//  Posicion.h
//  Implementation of the Class Posicion
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_)
#define EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_
#include "Orientacion.h"

/**
 * Clase que indentifica la posicion un elemento en el mapa
 */
class Posicion
{
private:
	int idArista;
	int posicionArista;
	Orientacion direccion;	

public:
	
	Posicion();
	
	Posicion( int idArista, int posicionArista, Orientacion direccion );
	
	virtual ~Posicion();
	
	int getArista()const;
	
	int getPosicionArista()const;
	
	Orientacion getDireccion();
	
	void setArista( int idArista );
	
	void setPosicionArista( int posicionArista );
	
	void setDireccion( Orientacion orientacion );
	
	

};
#endif // !defined(EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_)
