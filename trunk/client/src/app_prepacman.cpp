#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include "textura.h"
#include "camara.h"
#include "Parser.h"
#include "Request.h"

#define ANCHOL 6
#define LARGOL 10

using namespace std;


Textura	texPiso;
Textura	texPared;
/*	
 x = -3;//corro el escenario a la izquierda 3 posiciones ya que dibuja la tabla desde izq-abajo
 y = -0.5;//bajo el escenario 0.5 en eje y. Este valor sera fijo
 z = 0.5;
*/
Camara camara(-3,-0.5,0.5);
GLfloat angcuad=0;
//PARED HORIZONTAL
	int PH[LARGOL+1][ANCHOL] = {
	{    1,   1,   1,   1,   1,   1 },
	{    0,   0,   0,   0,   0,   0 },
	{    0,   0,   0,   0,   0,   0 },
	{    0,   0,   0,   0,   0,   0 },
	{    0,   0,   0,   0,   0,   0 },
	{    0,   0,   0,   0,   0,   0 },
	{    1,   1,   0,   0,   1,   1 },
	{    0,   0,   1,   1,   0,   0 },
	{    0,   0,   0,   0,   0,   1 },
	{    0,   1,   1,   0,   1,   0 },
	{    1,   1,   1,   1,   1,   1 },
};

//PARED VERTICAL
	int PV[LARGOL][ANCHOL+1] = {
	{    1,   0,   1,   0,   1,   0,   1 },
	{    1,   0,   1,   0,   1,   0,   1 },
	{    1,   0,   1,   0,   1,   0,   1 },
	{    1,   0,   1,   0,   1,   0,   1 },
	{    1,   0,   1,   0,   1,   0,   1 },
	{    1,   0,   1,   0,   1,   0,   1 },
	{    1,   0,   0,   0,   0,   1,   1 },
	{    1,   0,   0,   1,   0,   0,   1 },
	{    1,   0,   1,   0,   1,   0,   1 },
	{    1,   0,   0,   0,   1,   0,   1 },
	};



void idleEvent() {
	angcuad += 1;
	glutPostRedisplay();
}



void displayEvent(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camara.update();
	
	// dibujo del laberinto
	
	int i, j;

	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);


	//paredes de frente y de atras
	for (i = 0; i < LARGOL+1; i++ ) {
		for (j = 0; j < ANCHOL; j++ ) {
			if ( PH[i][j] != 0 ) {				
				if ( camara.getZ() <= i ) {
	               glBindTexture(GL_TEXTURE_2D, texPared.getId());
				   glBegin( GL_QUADS );
				     glTexCoord2f(0,0); glVertex3f( j, 0, -i );
				     glTexCoord2f(1,0); glVertex3f( j+1, 0, -i );
				     glTexCoord2f(1,1); glVertex3f( j+1, 1, -i );
				     glTexCoord2f(0,1); glVertex3f( j, 1, -i );
				   glEnd();
				}
				else {  
	               glBindTexture(GL_TEXTURE_2D, texPared.getId());
				   glBegin( GL_QUADS );
				     glTexCoord2f(0,0); glVertex3f( j+1, 0, -i );
				     glTexCoord2f(1,0); glVertex3f( j, 0, -i );
				     glTexCoord2f(1,1); glVertex3f( j, 1, -i );
				     glTexCoord2f(0,1); glVertex3f( j+1, 1, -i );
				   glEnd();
				}
			}
		}
	}
	//paredes de los costados derecho e izquierdo
	glColor3f(1,1,1);
	for (i = 0; i < LARGOL; i++ ) {
		for (j = 0; j < ANCHOL+1; j++ ) {
			if ( PV[i][j] != 0 ) {
				if ( -camara.getX() <= j ) {
	               glBindTexture(GL_TEXTURE_2D, texPared.getId());
				   glBegin( GL_QUADS );
				     glTexCoord2f(0,0); glVertex3f( j, 0, -i-1 );
				     glTexCoord2f(1,0); glVertex3f( j, 0, -i );
				     glTexCoord2f(1,1); glVertex3f( j, 1, -i );
				     glTexCoord2f(0,1); glVertex3f( j, 1, -i-1 );
				   glEnd();
				}
				else {
	               glBindTexture(GL_TEXTURE_2D, texPared.getId());
				   glBegin( GL_QUADS );
				     glTexCoord2f(0,0); glVertex3f( j, 0, -i );
				     glTexCoord2f(1,0); glVertex3f( j, 0, -i-1 );
				     glTexCoord2f(1,1); glVertex3f( j, 1, -i-1 );
				     glTexCoord2f(0,1); glVertex3f( j, 1, -i );
				   glEnd();
				}
			}
		}
	}

	// piso
    glBindTexture(GL_TEXTURE_2D,texPiso.getId());
	glColor3f(0.7,0.7,0.7 );
	for (i = 0; i < LARGOL; i++ ) {
		for (j = 0; j < ANCHOL; j++ ) {
			glBegin( GL_QUADS );
				glTexCoord2f(0,0); glVertex3f( j, 0, -i );
				glTexCoord2f(1,0); glVertex3f( j+1, 0, -i );
				glTexCoord2f(1,1); glVertex3f( j+1, 0, -i-1 );
				glTexCoord2f(0,1); glVertex3f( j, 0, -i-1 );
			glEnd();
		}
	}

	glDisable( GL_TEXTURE_2D );

	glPushMatrix();
	// al centro de la cuadrícula (0,7) del laberinto
	glTranslatef( 0+0.5, 0.5, -7-0.5);
	glRotatef( angcuad, 1,1,1 );
	glColor3f(0,0,1);
	glutWireSphere( 0.1, 10, 10 );
	glPopMatrix();


	glPushMatrix();
	// al centro de la cuadrícula (2,9) del laberinto
	glTranslatef( 2+0.5, 0.5, -9-0.5);
	glRotatef( -angcuad, 1,1,1 );
	glColor3f(0,1,1);
	glutWireSphere( 0.1, 10, 10 );
	glPopMatrix();

	// muestra la escena
	glutSwapBuffers();
}

void finalizarJuego()
{
	exit(EXIT_SUCCESS);
}

void tecladoEvent( int key, int Xx, int Yy ) {
		
	switch ( key ) {
		case GLUT_KEY_UP:    
			camara.ChkWall(camara.getX()-camara.getDtx(),camara.getZ()+camara.getDtz());
			break;
		case GLUT_KEY_DOWN:  
			camara.ChkWall(camara.getX()+camara.getDtx(),camara.getZ()-camara.getDtz()); 
			break;
		case GLUT_KEY_LEFT:
			camara.decAng(2);			
			camara.move();							
			break;
		case GLUT_KEY_RIGHT: 
			camara.incAng(2);			
			camara.move();					
			break;		
	}
	glutPostRedisplay();
}

void reshapeEvent(GLsizei width, GLsizei height) {
	// establecer el área de visualizacion en la ventana
	glViewport(0,0,width,height);

	// seleccionar la matriz de Proyección
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Vista en Perspectiva
	gluPerspective(45,(GLfloat)width/(GLfloat)height,  0.01, 100);

	// Restaurar a la matriz del Modelo (escena)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

} 

// Termina la ejecucion del programa cuando se presiona ESC
void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
    {
	 	case KEY_ESC: 
			finalizarJuego();				
			break;
    }
} 

int comenzarJuego(Request* req)
{
	int err=0;
	err = req->play();
	return err;
}

void iniciarGraficos(int argc, char** argv)
{
	glutInit( &argc, argv );	
	glutInitWindowSize( 500, 400 );
	glutInitWindowPosition( 100, 100 );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow( "PACMAN 3D" );

	glEnable(GL_TEXTURE_2D);
	if(!texPiso.cargarTGA("piso.tga")) {
		printf("Error cargando textura\n");
		exit(-1);
	}
	if(!texPared.cargarTGA("ladri.tga")) { 
		printf("Error cargando textura\n");
		exit(-1);
	}
		
	glEnable( GL_DEPTH_TEST );
	
    glutReshapeFunc (reshapeEvent);
	glutDisplayFunc( displayEvent );
	glutSpecialFunc( tecladoEvent );
	glutKeyboardFunc(keyboard);
	glutIdleFunc( idleEvent );		
	glutMainLoop();
}


int main(int argc, char** argv) {
	int port=0,err=0;
	std::string host="";
	
	Parser::validarArgumentos(argc,argv,&host,&port);
	
	/* Genera la conexion */
	Request* req = new Request(host,port);
	
	/* Comienza a jugar. */
	iniciarGraficos(argc, argv);
	err = comenzarJuego(req);

    /* Libera la conexion */
	delete req;
    
	/* Sale con el codigo de retorno correspondiente */
	return err;	
} 


