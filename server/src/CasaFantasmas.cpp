///////////////////////////////////////////////////////////
//  CasaFantasmas.cpp
//  Implementation of the Class CasaFantasmas
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "CasaFantasmas.h"


CasaFantasmas::CasaFantasmas( int posicion, Orientacion orientacion): Elemento( posicion, orientacion )
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

//Vector con los id de los vertice que compone la casa, menos la entrada
tVecVerticeId* CasaFantasmas::getVerticesId()
{
	return &vertices;
}
	
void CasaFantasmas::setVerticesId(tVecVerticeId& vertices)
{
	this->vertices=vertices;
}


