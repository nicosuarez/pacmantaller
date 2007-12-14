///////////////////////////////////////////////////////////
//  PowerUp.cpp
//  Implementation of the Class PowerUp
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "PowerUp.h"


PowerUp::PowerUp( int posicion, Orientacion orientacion ):Elemento( posicion, orientacion )
{
	
}

PowerUp::PowerUp( int posicion, Coordenada coord, Orientacion orientacion ):Elemento( posicion, coord, orientacion )
{
	
}

PowerUp::~PowerUp(){

}

tipoElemento PowerUp:: getTipo()const
{
	return tPowerup;
}


/**
 * Metodo que pertmite renderizar el objeto en la pantalla
 */
void PowerUp::renderizar(){	
	
	glPushMatrix();	
	glTranslatef(coord.x , coord.y, coord.z);
	//glRotatef( angcuad, 1,1,1 );
	glRotatef( 90, 1,1,1 );
	glColor3f(0,0,1);
	glutSolidSphere( 0.06, 10, 10 );
	glPopMatrix();	
		
}

bool PowerUp::operator==( tipoElemento tipo) const
{
	return tipo == tPowerup;
}
