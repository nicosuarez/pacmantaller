///////////////////////////////////////////////////////////
//  Pastilla.cpp
//  Implementation of the Class Pastilla
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "Pastilla.h"


Pastilla::Pastilla( int posicion, Orientacion orientacion ):Elemento( posicion, orientacion )
{

}


Pastilla::~Pastilla()
{

}


tipoElemento Pastilla::getTipo()const
{
	return tPastilla;
}

/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void Pastilla::renderizar(){
	glColor3f(1,1,1);
	glPushMatrix();	
	glTranslatef(coord.x , coord.y, coord.z);
	//glRotatef( angcuad, 1,1,1 );
	glRotatef( 90, 1,1,1 );
	glColor3f(1,1,0);
	glutSolidSphere( 0.06, 10, 10 );
	glPopMatrix();	
}

bool Pastilla::operator==( tipoElemento tipo) const
{
	return tipo == tPastilla; 
}
