///////////////////////////////////////////////////////////
//  Posicion.h
//  Implementation of the Class Posicion
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_)
#define EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_

#include <iostream>
#include "Elemento.h"

//Se definen las direcciones en las aristas.
#define N_E 0  //Direccion Norte/Este
#define S_O 1  //Direccion Sur/Oeste

//Se definen el rango de posiciones dentro de las aristas.
#define INICIO_ARISTA 0  //Posicion inicial del arista si el personaje viene de N o E
#define FIN_ARISTA 63  //Posicion inicial del arista si el personaje viene de S o O

/*
 * NOTA: La posicion relativa a la arista se mantiene teniendo en cuenta que 
 * a la hora de tener que agarrar una arista N/E se setea la posicion en 
 * INICIO_ARISTA y si la arista es S/O se setea la posicion del personaje 
 * en FIN_ARISTA.
 */
 


/**
 * Clase que indentifica la posicion un elemento en el mapa
 */
class Posicion
{
private:
	int idVertice; //Vertice desde donde partio
	int idArista; //Identificador de la arista
	int posicionArista; //Posicion dentro de la arista 0-63
	int direccion; //Direccion sobre la arista NORTE/SUR ESTE/OESTE
	
public:
	
	Posicion();
	
	Posicion(int idVertice,int direccion);
	
	Posicion(int idVertice,int idArista,int posicionArista,int direccion);
	
	Posicion( const Posicion &posicion );
	
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
	
	static int getPosAristaInicial(int orientacion);
	
	bool estaEnUnVertice();
	
	/**
	 * Posicion del personaje en el mapa
	 */
	void SetPosicion(int idVertice,int idArista,int posicionArista,int direccion);
	
	/**
	 * Posicion en un vertice, sin ninguna arista asignada, no puede avanzar hasta que no se
	 * realice un cambio de direccion
	 */
	void SetPosicion(int idVertice,int direccion);
	
	/**
	 * Obtiene la direccion inicial del personaje dependiendo de la orientacion de la arista.
	 */
	static int getDireccionInicial(Orientacion orientacion);
};
#endif // !defined(EA_A9FE7C93_BFCB_4344_8489_32A4092889A9__INCLUDED_)
