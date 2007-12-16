///////////////////////////////////////////////////////////
//  Bonus.cpp
//  Implementation of the Class Bonus
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "Bonus.h"


Bonus::Bonus( int posicion, Orientacion orientacion): Elemento( posicion, orientacion )
{

}

Bonus::Bonus( int posicion, Coordenada coord, Orientacion orientacion ): Elemento( posicion, coord, orientacion )
{
	
}

Bonus::~Bonus(){

}

tipoElemento Bonus::getTipo()const
{
	return tBonus;
}

/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void Bonus::renderizar(){
	//glColor3f(1,1,1);
	if (estado == Aparece) {
		glPushMatrix();	
		glTranslatef(coord.x , coord.y, coord.z);
		//glRotatef( angcuad, 1,1,1 );
		glRotatef( 90, 1,1,1 );
		glColor3f(1.0,0.0,0);
		glutSolidSphere( 0.06, 10, 10 );
		glPopMatrix();
	}

}

bool Bonus::operator==( tipoElemento tipo) const
{
	return tipo == tBonus;
}
