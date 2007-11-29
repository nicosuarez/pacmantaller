#ifndef CAMARA_H
#define CAMARA_H

#include <GL/gl.h>
#include <GL/glut.h>
#include "math.h"

#define ANCHOL 6
#define LARGOL 10

class Camara {

	private:		
		float x,y,z, ang, paso, dtx, dtz;
		
	public: 
		
		Camara(float x,float y, float z): x(x), y(y), z(z) {
			ang = 0;
			paso = 0.15;
			dtx = 0;
			dtz = paso;
		};

		float getX() {return x;}
		float getY() {return y;}
		float getZ() {return z;}
		float getDtx() {return dtx;}
		float getDtz() {return dtz;}

		//~Camara();				
		int ChkWall(float x2, float z2 ); 
		void move(); 
		float dtr( float d ); 		
		void update(); 
		void decAng(float angulo); 
		void incAng(float angulo); 
};	

#endif
