///////////////////////////////////////////////////////////
//  Posicion.h
//  Implementation of the Class Posicion
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_)
#define EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_

#include <iostream>

/**
 * Clase que indentifica la posicion un elemento en el mapa
 */
class Posicion
{
private:
	int idArista; //Identificador de la arista
	int posicionArista; //Posicion dentro de la arista 0-63
	int direccion; //Direccion sobre la arista NORTE/SUR ESTE/OESTE
	int idVertice; //Vertice desde donde partio

public:
	
	Posicion();
	
	Posicion( const Posicion & posicion);
	
	Posicion(int idArista,int posicionArista,int direccion,int idVertice);
	
	virtual ~Posicion();
	
	int getArista()const;
	
	int getVertice()const;
	
	int getPosicionArista()const;
	
	int getDireccion()const;
	
	void setArista( int idArista );
	
	void setPosicionArista( int posicionArista );
	
	void setDireccion( int direccion );
	
	void operator=( const Posicion &posicion );
	
	friend std::ostream& operator <<( std::ostream& os, const Posicion &p) 
 	{ 
     	os << "("<< p.idVertice << "," << p.idArista << "," << p.posicionArista << "," << p.direccion << ")"; 
     	// return ostream object 
     	return os; 
 	}

};
#endif // !defined(EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_)
