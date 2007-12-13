///////////////////////////////////////////////////////////
//  Cliente.cpp
//  Implementation of the Class Cliente
//  Created on:      21-Nov-2007 23:40:22
///////////////////////////////////////////////////////////

#include "Cliente.h"
#include "app_prepacman.cpp"
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include "textura.h"
#include "Camara.h"
#include "Parser.h"
#include "Request.h"
#include "Vertice.h"
#include <vector>

using namespace std;

EnviarMensaje *ptrEnviar = NULL;

#define LONGVERTICE 2
#define MAXPOSARISTA 64
#define ALTURAPACMAN 0.57
#define ALTURAITEMS 0.5
#define cantBonus 3
#define cantPower 2

Textura	texPiso;
Textura	texPared;

vector<Vertice> vecVertices;
vector<Vertice> vecPastillas;

Camara camara(Coordenada(3,0.6,-1),Coordenada(4,0.6,-1), Coordenada(0,1,0));

/*int ph[filas+1][cols] = {
	{ 1,   1,   1, },
	{ 0,   0,   0, },
	{ 1,   0,   0, },
	{ 1,   1,   1, },
};

int pv[filas][cols+1] = {
	{ 1,   0,   0,  1 },
	{ 1,   1,   0,  1 },
	{ 1,   0,   1,  1 },
};*/

GLfloat angcuad=0;

void idleEvent() {
	angcuad += 1;
	
	glutPostRedisplay();
}


void crearVerticesMapa() {//proviene de leer ALTO y ANCHO de init

	Coordenada pos;
	int filas=Modelo::getInstance()->getMapa()->getAlto();
	int cols =Modelo::getInstance()->getMapa()->getAncho();
	
	int id;
	for (int i=0; i<filas; i++) {
		for (int j=0; j<cols; j++) {
			
			pos.x= j*LONGVERTICE+1;
			pos.y= 0;
			pos.z= -(i*LONGVERTICE+1); 
			//cout<<"---->xyz = "<<pos.x<<" "<<pos.y<<" "<<pos.z<<endl;			
			//int id= i*cols + j;
			id = ((filas-1)-i)*cols+j;
			//cout<<"---->id = "<<id<<endl;
			Vertice vert(id,pos);
			vecVertices.push_back(vert);
		}
	}
}

Coordenada buscarCoordenada(int idVert) {

	Coordenada coord;
	int id;
	size_t i=0;
	bool encontrado=false;
	while (!encontrado && i<vecVertices.size()) {
		id = vecVertices[i].getIdVertice();	
		if (id==idVert) {
			coord= vecVertices[i].getCoordenada();
			encontrado=true;
		}
		else {
			i++;
		}
	}
	return coord;
}

void sim_leerElementos() {
	Elemento* elem;
	std::list<Elemento*>* elementos = Modelo::getInstance()->getElementos();
	//tSalidaPacman, tCasaFantasmas, tPowerup, tBonus, tPastilla
	while (!elementos->empty()) {
		elem= elementos->front();
		switch ((int)elem->getTipo()) {
			case (int)tPastilla:  
			{	
				Coordenada coord = buscarCoordenada(elem->getPosicion());
				coord.y=ALTURAITEMS;
				Vertice verticePastilla(elem->getPosicion(),coord);
				vecPastillas.push_back(verticePastilla);
				break;
				/*cout<<"posPacman: "<<elem.posicion<<endl;
				
				Posicion posPacman=buscarPos(elem.posicion);
				posPacman.y=ALTURAPACMAN;
				cout<<"posPacman coord: "<<posPacman.x<<" "<<posPacman.y<<" "<<posPacman.z<<endl;
				Vertice verticePacman(elem.posicion,posPacman);
				initPacman.setVertice(verticePacman);
				initPacman.setOrientacion(elem.orientacion);
				cout<<"orientacion: "<<elem.orientacion<<endl;
				break;*/
			}
			/*case 1: {
				Posicion posFantasma=buscarPos(elem.posicion);
				posFantasma.y=ALTURAPACMAN;
				Vertice verticeFantasma(elem.posicion,posFantasma);
				initFantasma.setVertice(verticeFantasma);
				initFantasma.setOrientacion(elem.orientacion);
				break;
			}
			case 2: {								
				Posicion pos=buscarPos(elem.posicion);
				Vertice vert(elem.posicion,pos);
				vecPower.push_back(vert);
				break;
			}
			case 3: {
				Posicion pos=buscarPos(elem.posicion);
				Vertice vert(elem.posicion,pos);
				vecBonus.push_back(vert);
				break;
			}*/
		}
		elementos->pop_front();
	}
}


//Pacman initPacman;//salida del pacman
//Fantasma initFantasma;//salida del fantasma
vector<Vertice> vecBonus;
vector<Vertice> vecPower;

/*void displayEvent(void) {

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
*/

//*******************************************************************//
//				METODOS PARA DIBUJAR EN PANTALLA						
//*******************************************************************//
void transformarParedes(Mapa* mapa) {
	int filas= mapa->getAlto();
	int cols= mapa->getAncho();
	int** ph=mapa->getph();
	int** pv=mapa->getpv();
	
	int phaux[filas+1][cols];  
	int pvaux[filas][cols+1];  
	for (int i = filas; i >= 0; i-- ) {
		for (int j = 0; j < cols; j++ ) {
			phaux[filas-i][j]=ph[i][j];			
		}
	
	}
	for (int i = filas-1; i >= 0; i-- ) {
		for (int j = 0; j < cols+1; j++ ) {
			pvaux[filas-1-i][j]=pv[i][j];			
		}	
	}


	for (int i = 0; i < filas+1; i++ ) {
		for (int j = 0; j < cols; j++ ) {
			ph[i][j]=phaux[i][j];			
		}
	
	}
	for (int i = 0; i <filas; i++ ) {
		for (int j = 0; j < cols+1; j++ ) {
			pv[i][j]=pvaux[i][j];			
		}	
	}
	
}

void dibujarParedH(Mapa* mapa) {
	int iaux,jaux;
	int filas= mapa->getAlto();
	int cols= mapa->getAncho();
	int** ph=mapa->getph();
	
	glBindTexture(GL_TEXTURE_2D, texPared.getId());
	for (int i = 0; i < filas+1; i++ ) {//en z de 0 a 10 (11 puntos en z)
		for (int j = 0; j < cols; j++ ) {//me muevo en x
	
			if ( ph[i][j] == 1 ) {					
				iaux=2*i;
				jaux=2*j;				
				glBegin( GL_QUADS );				 
					glTexCoord2f(0,0); glVertex3f( jaux, 0, -iaux );
					glTexCoord2f(1,0); glVertex3f( jaux+2, 0, -iaux);
					glTexCoord2f(1,1); glVertex3f( jaux+2, 1, -iaux);
					glTexCoord2f(0,1); glVertex3f( jaux, 1, -iaux);
				glEnd();						
			}
		}
	}
}

void dibujarParedV(Mapa* mapa) {
	int iaux,jaux;
	int filas= mapa->getAlto();
	int cols= mapa->getAncho();
	int** pv=mapa->getpv();
	
	glBindTexture(GL_TEXTURE_2D, texPared.getId());
	for (int i = 0; i <filas; i++ ) {
		for (int j = 0; j < cols+1; j++ ) {	
			if ( pv[i][j] == 1 ) {	
				iaux=2*i;
				jaux=2*j;					            
				glBegin( GL_QUADS );				    
					glTexCoord2f(0,0); glVertex3f( jaux, 0,-iaux-2 );
					glTexCoord2f(1,0); glVertex3f( jaux, 0, -iaux);
					glTexCoord2f(1,1); glVertex3f( jaux, 1, -iaux);
					glTexCoord2f(0,1); glVertex3f( jaux, 1,-iaux-2 );
				glEnd();
			}
		}
	}
	
}

void dibujarSuelo(Mapa* mapa) {
	int iaux,jaux;
	int filas= mapa->getAlto();
	int cols= mapa->getAncho();
	
	glBindTexture(GL_TEXTURE_2D,texPiso.getId());
	for (int i = 0; i < filas; i++ ) {
		for (int j = 0; j < cols; j++ ) {
			iaux=2*i;
			jaux=2*j;				
			glBegin( GL_QUADS );
				glTexCoord2f(0,0); glVertex3f( jaux, 0, -iaux );
				glTexCoord2f(1,0); glVertex3f( jaux+2, 0, -iaux );
				glTexCoord2f(1,1); glVertex3f( jaux+2, 0, -iaux-2 );
				glTexCoord2f(0,1); glVertex3f( jaux, 0, -iaux-2 );
			glEnd();
		}
	}
}

void dibujarBonus() {

	/*Coordenadas pos;
	for (int i=0;i<vecBonus.size();i++) {
		glPushMatrix();	
		pos=vecBonus[i].getPosicion();
		pos.y=ALTURAITEMS;
		glTranslatef(pos.x , pos.y, pos.z);
		glRotatef( angcuad, 1,1,1 );
		glColor3f(0,0,1);
		glutSolidSphere( 0.07, 18, 15 );
		glPopMatrix();	
	}*/
}

void dibujarPastillas() {
	glColor3f(1,1,1);
	Coordenada pos;
	for (size_t i=0;i<vecPastillas.size();i++) {
		glPushMatrix();	
		pos=vecPastillas[i].getCoordenada();
		glTranslatef(pos.x , pos.y, pos.z);
		glRotatef( angcuad, 1,1,1 );
		glColor3f(1,1,0);
		glutSolidSphere( 0.06, 10, 10 );
		glPopMatrix();	
	}
	
}

void render(void) {
	Mapa* mapa=Modelo::getInstance()->getMapa();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	camara.update(); 
	
	glEnable(GL_TEXTURE_2D);
	glColor3f(1,1,1);//Selecciona el color actual con el que dibujar

	dibujarParedH(mapa);	
	dibujarParedV(mapa);
	dibujarSuelo(mapa); 	
	
	
	glDisable( GL_TEXTURE_2D );		

	dibujarBonus();
	dibujarPastillas();

	glutSwapBuffers();
}


void finalizarJuego()
{
	exit(EXIT_SUCCESS);
}

void tecladoEvent( int key, int Xx, int Yy ) {
		
	switch ( key ) {
		case GLUT_KEY_UP:    
			camara.moverAdelante(); 
			ptrEnviar->enviarMensaje( new Key(KEY_ARRIBA) );
			break;
		case GLUT_KEY_DOWN:  
			camara.move(-1); 
			ptrEnviar->enviarMensaje( new Key(KEY_ABAJO) );
			break;
		case GLUT_KEY_LEFT:
			camara.moverIzq(); 
			ptrEnviar->enviarMensaje( new Key(KEY_IZQUIERDA) );
			break;
		case GLUT_KEY_RIGHT: 
			camara.moverDer(); 
			ptrEnviar->enviarMensaje( new Key(KEY_DERECHA) );
			break;		
		case GLUT_KEY_HOME://sube la camara= baja el escenario			
			camara.strafeUp(1);
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

void initTexturas () {

	if(!texPiso.cargarTGA("Imagenes/suelo.tga")) {
		printf("Error cargando textura\n");
		exit(-1);
	}
	if(!texPared.cargarTGA("Imagenes/pared.tga")) { 
		printf("Error cargando textura\n");
		exit(-1);
	}
}

// Termina la ejecucion del programa cuando se presiona ESC
void keyboard(unsigned char key, int x, int y)
{
	switch (key) 
    {
	 	case KEY_ESC:
	 		ptrEnviar->enviarMensaje( new Key(KEY_ESCAPE) );
			//finalizarJuego();				
			break;
    }
} 

int comenzarJuego(Request* req)
{
	int err=0;
	err = req->play();
	return err;
}

/*void setearCamaraInit() {
	
	camara.setSpeed(2/8.0);//no se usará
	//Coordenada pos = (initPacman.getVertice()).getCoordenada();
	//cout<<"CamaraInit--> pos ojo= "<<pos.x<<" "<<pos.y<<" "<<pos.z<<endl;
	camara.setOjo(pos);
	//cout<<"CamaraInit--> Orientacion "<<initPacman.getOrientacion()<<endl;
	switch (initPacman.getOrientacion()) {
		case 0: {
			pos.z -= 1;
			break;
		}
		case 1: {
			pos.z += 1;
			break;
		}
		case 2: {
			pos.x += 1;
			break;
		}
		case 3: {
			pos.x -= 1;
			break;
		}
	}
	camara.setCentro(pos);
	//cout<<"CamaraInit--> pos centro= "<<pos.x<<" "<<pos.y<<" "<<pos.z<<endl;
}*/

void  iniciarGraficos(int argc, char** argv)
{
	Mapa* mapa=Modelo::getInstance()->getMapa();
	
	glutInit( &argc, argv );	
	glutInitWindowSize( 500, 400 );
	glutInitWindowPosition( 100, 100 );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow( "PACMAN 3D" );	
	glEnable(GL_TEXTURE_2D);

	
	initTexturas();		
	transformarParedes(mapa);
	crearVerticesMapa();//del INIT
	//crearVecPastillas();// no se usará
	//sim_llenarElementos();//del INIT
	sim_leerElementos();//del INIT
	//setearCamaraInit();	
	//initPacman.setIdPlayer(idPlayer);//del STATUS
	//sim_llenarPlayer(); 
	//sim_llenarElementoStatus(); 
	//sim_leerPlayer(); 
	glEnable( GL_DEPTH_TEST );	

    glutReshapeFunc (reshapeEvent);
	glutDisplayFunc( render );
	glutSpecialFunc( tecladoEvent );
	glutIdleFunc( idleEvent );		
	glutKeyboardFunc( keyboard );
	glutMainLoop();
}



Cliente::Cliente(const string& host,Socket::port_type puerto)
{
	  this->skCliente = new Socket(host,puerto);
	  this->finalizoJuego = false;
	  this->cerrarServidor=false;
	  enviarMensaje = new EnviarMensaje( skCliente );
}
/*----------------------------------------------------------------------------*/
Cliente::~Cliente(){
	delete skCliente;
	delete enviarMensaje;
}
/*----------------------------------------------------------------------------*/
int Cliente::ejecutar(int cantArg,char* argv[]){
	Modelo* modelo = Modelo::getInstance();
	modelo->setFinalizoJuego(false);
	modelo->setEnviarMensaje( enviarMensaje );
	
	//El jugador establece conexion con el servidor.
	this->recibirMensajes();
	
	//Esperar a recibir el mesaje init
	modelo->getRecibiMensajeInitEvent().esperar();
	
	//Comienza el juego.
	this->comenzarJuego(cantArg,argv);
	
	this->thrRecibirMensajes->join();
	return 0;
}

void Cliente::recibirMensajes()
{
    /* Si logro conectar */
	if(this->skCliente){
		this->thrRecibirMensajes = new RecibirMensaje(this->skCliente);
		this->thrRecibirMensajes->run();		
	}
	else
	{
		exit(ERR_CONEXION_SOCKET);
	}	
}

/*----------------------------------------------------------------------------*/
/**
 * Se ejecuta el hilo principal del juego el del modelo.
 */
void Cliente::comenzarJuego(int cantArg,char* argv[]){
	
	//Se instancia el modelo. Singleton
	//Modelo::setInstance(cantArg,argv);

	//Comienza el juego...
	//Modelo::getInstance()->run();
	
	//Espera que finalice...
	//Modelo::getInstance()->join();
	this->enviarMensaje->run();
	ptrEnviar = this->enviarMensaje;
	iniciarGraficos(cantArg,argv);
	Modelo::getInstance()->setFinalizoJuego( true );
	this->enviarMensaje->join();
}






