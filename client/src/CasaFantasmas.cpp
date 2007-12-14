///////////////////////////////////////////////////////////
//  CasaFantasmas.cpp
//  Implementation of the Class CasaFantasmas
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "CasaFantasmas.h"


CasaFantasmas::CasaFantasmas( int posicion, Orientacion orientacion ): Elemento( posicion, orientacion )
{

}

CasaFantasmas::CasaFantasmas( int posicion, Coordenada coord, Orientacion orientacion ): Elemento( posicion, coord, orientacion )
{
	
}

CasaFantasmas::~CasaFantasmas(){

}

tipoElemento CasaFantasmas:: getTipo()const
{
	return tCasaFantasmas;
}

/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void CasaFantasmas::renderizar(){
	

}

bool CasaFantasmas::operator==( tipoElemento tipo) const
{
	return tipo == tCasaFantasmas;
}
