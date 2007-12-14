#ifndef COORDENADA_H
#define COORDENADA_H

#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h> 
#include <GL/glut.h>

#include <fstream>
#include <stdio.h>
#include "math.h"

using namespace std;

class Coordenada {

	public: 				

		float x,y,z;  //coordenadas x,y,z	
		Coordenada (); 
		Coordenada (float x, float y, float z);		
		Coordenada(const Coordenada &coord);		
		~Coordenada();	

		const Coordenada& operator= (const Coordenada &coord); 
		Coordenada operator +(const Coordenada& coord); 
		Coordenada operator -(const Coordenada& coord);
		Coordenada operator *(const float& a);
	
};

#endif
