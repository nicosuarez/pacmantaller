///////////////////////////////////////////////////////////
//  Elemento.cpp
//  Implementation of the Class Elemento
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "Elemento.h"


Elemento::Elemento(){

}



Elemento::~Elemento(){

}





Posicion Elemento::GetPosicion(){

	return posicion;
}


/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void Elemento::renderizar(){

}


void Elemento::SetPosicion(Posicion newVal){

	posicion = newVal;
}