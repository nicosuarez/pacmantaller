///////////////////////////////////////////////////////////
//  Posicion.h
//  Implementation of the Class Posicion
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_)
#define EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_

#include <iostream>

//Se definen las direcciones en las aristas.
#define N_E 0  //Direccion Norte/Este
#define S_O 1  //Direccion Sur/Oeste

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
	
	Posicion(int idVertice);
	
	Posicion(const Posicion & posicion);
	
	Posicion(int idVertice,int idArista,int posicionArista,int direccion);
	
	virtual ~Posicion();
	
	int getArista()const;
	
	int getVertice()const;
	
	int getPosicionArista()const;
	
	int getDireccion()const;
	
	void setArista( int idArista );
	
	void setPosicionArista( int posicionArista );
	
	void setDireccion( int direccion );
	
	void setVertice( int idVertice );
	
	void operator=( const Posicion &posicion );
	
	friend std::ostream& operator <<( std::ostream& os, const Posicion &p) 
 	{
		if(p.direccion==N_E)
			os << "Pos("<< p.idVertice << "," << p.idArista << "," << p.posicionArista << "," << "N_E" << ")"; 
		else
			os << "Pos("<< p.idVertice << "," << p.idArista << "," << p.posicionArista << "," << "S_O" << ")"; 
      
     	return os; 
 	}

	void cambiarDireccion();
};
#endif // !defined(EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_)
