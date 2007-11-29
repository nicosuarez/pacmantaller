#include "camara.h"

extern int PH[LARGOL+1][ANCHOL]; 
extern int PV[LARGOL][ANCHOL+1];
 
int Camara::ChkWall(float x2, float z2 ) {
 
	int cx1, cz1, cx2, cz2;
	float x1, z1;
	int i, j, ok;
	
	x1 = -x;
	z1 = z;
	x2 = -x2;	
	ok = 1;
		
	if ( x2 <= 0 || z2 <= 0 || x2 >= ANCHOL || z2 >= LARGOL ) {// fuera del laberinto?	
		return 0;
	}
	
	// cuadricula actual
	cx1 = int(x1);
	cz1 = int(z1);
	// cuadricula a donde se quiere mover
	cx2 = int(x2);
	cz2 = int(z2);

	if ( ! (cx1 == cx2 && cz1 == cz2) ) { //cambió de cuadrícula
		
		if ( cx1 == cx2 ) {// sólo cambió la cuadrícula de z		
			if ( cz2 > cz1 ) { 
				j = cx1; 
				i = cz1+1; 
			}
			else { 
				j = cx1; 
				i = cz1;   
			}
			if ( PH[i][j] != 0 )
				ok = 0;
		}
		else
		if ( cz1 == cz2 ) {// sólo cambió la cuadrícula de x		
			if ( cx2 > cx1 ) { 
				j = cx1+1; 
				i = cz1;   
			}
			else { 
				j = cx1;   
				i = cz1;   
			}
			if ( PV[i][j] != 0 )
				ok = 0;
		}
		else {  // cambió en las dos cuadrículas
			// bloquearemos el paso si hay al menos una pared en la intersección			
			if ( cx2 > cx1 )
				if ( cz2 > cz1 ) {// derecha arriba				
					if ( PV[cz1][cx2] != 0 || PV[cz2][cx2] != 0 ||
						PH[cz2][cx1] != 0 || PH[cz2][cx2] != 0 )
						ok = 0;
				}
				else {// derecha abajo				
					if ( PV[cz1][cx2] != 0 || PV[cz2][cx2] != 0 ||
						PH[cz1][cx1] != 0 || PH[cz1][cx2] != 0 )
						ok = 0;
				}
			else
				if ( cz2 > cz1 ) {// izquierda arriba				
					if ( PV[cz1][cx1] != 0 || PV[cz2][cx1] != 0 ||
						PH[cz2][cx1] != 0 || PH[cz2][cx2] != 0 )
						ok = 0;
				}
				else {// izquierda abajo				
					if ( PV[cz1][cx1] != 0 || PV[cz2][cx1] != 0 ||
						PH[cz1][cx1] != 0 || PH[cz1][cx2] != 0 )
						ok = 0;
				}
		}
	}
	
	if ( ok ) {
		x = -x2;
		z = z2;		
	}
	return 0;
}


void Camara::move() {

	float angrad = dtr(ang);
	dtx = paso * sin(angrad);//paso es un coef para saber cuanto moverme al presionar tecla
	dtz = paso * cos(angrad);
}


float Camara::dtr( float d ) {
	return d*3.141592/180;
}

void Camara::update() {
	// traslada la escena al centro del espacio
	glRotatef( ang, 0,1,0 );//rotamos el angulo sobre el eje Y.
	glTranslatef( x, y, z );//nos movemos sobre los ejes X y Z. TODO Y es fija
}

void Camara::decAng(float angulo) {
	ang-=angulo;
}

void Camara::incAng(float angulo) {
	ang += angulo; 
}
