///////////////////////////////////////////////////////////
//  Posicion.h
//  Implementation of the Class Posicion
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_)
#define EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_
#include "AppSettings.h"

/**
 * Clase que indentifica la posicion un elemento en el mapa
 */
class Posicion
{
private:
	int idArista;
	int posicionArista;
	int direccion;	

public:
	
	Posicion();
	
	Posicion( const Posicion & posicion);
	
	Posicion( int idArista, int posicionArista, int direccion );
	
	virtual ~Posicion();
	
	int getArista()const;
	
	int getPosicionArista()const;
	
	int getDireccion()const;
	
	void setArista( int idArista );
	
	void setPosicionArista( int posicionArista );
	
	void setDireccion( int direccion );
	
	void operator=( const Posicion &posicion );
	
	

};
#endif // !defined(EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_)
