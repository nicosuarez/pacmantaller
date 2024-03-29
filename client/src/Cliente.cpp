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

Textura	texSuelo;
Textura	texPared;

int anchoVentana =400;
int altoVentana =300;

//Camara camara(Coordenada(3,0.6,-1),Coordenada(4,0.6,-1), Coordenada(0,1,0));


GLfloat angcuad=0;

void finalizarJuego()
{
	exit(EXIT_SUCCESS);
}

void idleEvent() {
	angcuad += 1;
	
	glutPostRedisplay();
}


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
	
	glBindTexture(GL_TEXTURE_2D,texSuelo.getId());
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
	Modelo *modelo = Modelo::getInstance();
	modelo->getMutexBonus().lock();
	tListBonus bonus = modelo->getBonus();
	tListBonus::iterator itBonus;
	for( itBonus = bonus.begin(); itBonus != bonus.end(); itBonus++ )
	{		
		(*itBonus)->renderizar();	
		
	}	
	modelo->getMutexBonus().unlock();
}

void dibujarPowerUp() {

	Modelo *modelo = Modelo::getInstance();
	modelo->getMutexPowers().lock();
	tListPower powers = modelo->getPowers();
	tListPower::iterator itPowers;
	
	for( itPowers = powers.begin(); itPowers != powers.end(); itPowers++ )
	{	
		(*itPowers)->renderizar();		
	}	
	modelo->getMutexPowers().unlock();
}

void dibujarPastillas() {
	Modelo *modelo = Modelo::getInstance();
	modelo->getMutexPastillas().lock();
	tListPastilla pastillas = modelo->getPastillas();
	tListPastilla::iterator itPastillas;
	for( itPastillas = pastillas.begin(); itPastillas != pastillas.end(); itPastillas++ )
	{			
		(*itPastillas)->renderizar();		
	}
	modelo->getMutexPastillas().unlock();
	
}
/*
void temp_setPosicionFantasma() {

	Coordenada coord,rot;
	coord.x=5;
	coord.y=0.3;
	coord.z=-5;
	
	rot.x=0.0;
	rot.y=-75.0;
	rot.z=0.0;
		
	Model* model = new Model();
	ObjLoader::cargarModelo(*model,OBJ_PATH_FANTASMA,TEX_PATH_FANTASMA);
	Personaje* fantasma = new Fantasma();
	fantasma->SetCoord(coord);
	fantasma->SetRotacion(rot);
	fantasma->SetModel(model);
	Modelo::getInstance()->getPersonajes().push_back(fantasma);

	coord.x=5.8;
	coord.y=1.3;
	coord.z=-5;
	
	rot.x=0.0;
	rot.y=180.0;
	rot.z=-100.0;
	Model* model2 = new Model();
	ObjLoader::cargarModelo(*model2,OBJ_PATH_PACMAN,TEX_PATH_PACMAN);
	Personaje* pac = new PacMan();
	pac->SetCoord(coord);
	pac->SetRotacion(rot);
	pac->SetModel(model2);
	Modelo::getInstance()->getPersonajes().push_back(pac);
		
}*/

void dibujarPersonajes() {
	
	Modelo *modelo = Modelo::getInstance();
	modelo->getMutexPersonajes().lock();
	tListPersonaje personajes = modelo->getPersonajes();
	tListPersonaje::iterator itPersonajes;
	for( itPersonajes = personajes.begin(); itPersonajes != personajes.end(); itPersonajes++ )
	{
		/*if ((*itPersonajes)->GetRol()==0)
			cout<<"renderizo pacman"<<endl;
		else
			cout<<"renderizo fantasma"<<endl;*/		
		
		(*itPersonajes)->renderizar();		
	}
	modelo->getMutexPersonajes().unlock();
}


//############################################
//############################################
void renderCadena(int x, int y, char *buf){
	glRasterPos2f (x, y);
	for (unsigned int i = 0; i < strlen(buf); i++)
		glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, buf[i]);
}


void dibujarPuntuacion() {

	int x, y;
	char buf[128];

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glMatrixMode (GL_MODELVIEW);
	//glLoadIdentity();

	//gluLookAt(0,0,0,0,0,-1,0.0f, 1.0f, 0.0f);		
		
	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D (0, anchoVentana, 0, altoVentana);
		glScalef (1.0f, -1.0f, 1.0f); // Snúum við y-ás
		glTranslatef (0, -anchoVentana, 0);
	
		glMatrixMode (GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
		
			glLineWidth (2.0f);
			sprintf (buf, " PUNTUACION %d",Modelo::getInstance()->getPuntuacion());			
			
			glPushMatrix();
				glScalef (1.1f, 1.1f, 1.1f);
				x =  anchoVentana / 2 - glutBitmapLength (GLUT_BITMAP_HELVETICA_18, (unsigned char *)buf) / 2;
				//x =  anchoVentana / 2;
				y = altoVentana - altoVentana/3;
				//y = altoVentana/2;
				glColor4f (0.4f, 0.4f, 0.7f, 0.5f);
				//renderCadena (x+1, y+1, buf);
				glColor4f (1.0f, 1.0f, 1.0f, 1.0f);
				renderCadena (x, y, buf);
			glPopMatrix();
		
		
			glMatrixMode (GL_PROJECTION);
		glPopMatrix();
		glMatrixMode (GL_MODELVIEW);
	glPopMatrix();

}
//############################################
//############################################

/**
 * Espera a recibir el proximo mapa (INIT) y comienza el nuevo nivel.
 */
void comenzarSiguienteNivel()
{
	Modelo* modelo = Modelo::getInstance();
	Mapa* mapa = modelo->getMapa();			
	std::cout << "Espera recibir el nuevo INIT\n";
	//Borra el mapa anterior
	delete mapa;
	mapa = NULL;
	
	//Se espera recibir el siguiente nivel
	modelo->getRecibiMensajeInitEvent().esperar();
	//Ajusta visualmente el nuevo mapa.
	transformarParedes( modelo->getMapa() );
	
	std::cout << "Termino la espera.. Comienza el nivel\n";
}
/**
 * Verifica si el juego termino o si hay  un proximo nivel espera a recibir el mapa.
 */
void verificarQueElJuegoContinue()
{
	Modelo* modelo = Modelo::getInstance();
	
	if( modelo->getFinalizoJuego() ) //Si finalizo el juego
		finalizarJuego();
	else if(modelo->getFinalizoNivel()) //Si cambio de nivel
		comenzarSiguienteNivel();
}

void render(void) {
	Modelo *modelo = Modelo::getInstance(); 
	verificarQueElJuegoContinue();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	modelo->getCamara().update(); 
	glEnable(GL_TEXTURE_2D);
	glColor3f(1,1,1);//Selecciona el color actual con el que dibujar
	modelo->getMutexMapa().lock();
	Mapa* mapa = modelo->getMapa();
	dibujarParedH(mapa);	
	dibujarParedV(mapa);
	dibujarSuelo(mapa); 	
	modelo->getMutexMapa().unlock();
	
	glDisable( GL_TEXTURE_2D );		
	
	glColor3f(1,1,1);

	dibujarPuntuacion();
	dibujarPastillas();
	dibujarPowerUp();
	dibujarBonus();
	dibujarPersonajes();
	
	glutSwapBuffers();

}

void tecladoEvent( int key, int Xx, int Yy ) {
		
	switch ( key ) {
		case GLUT_KEY_UP:    
			//camara.moverAdelante(); 
			ptrEnviar->enviarMensaje( new Key(KEY_ARRIBA) );
			break;
		case GLUT_KEY_DOWN:  
			//camara.move(-1); 
			ptrEnviar->enviarMensaje( new Key(KEY_ABAJO) );
			break;
		case GLUT_KEY_LEFT:
			//camara.moverIzq(); 
			ptrEnviar->enviarMensaje( new Key(KEY_IZQUIERDA) );
			break;
		case GLUT_KEY_RIGHT: 
			//camara.moverDer(); 
			ptrEnviar->enviarMensaje( new Key(KEY_DERECHA) );
			break;		
		case GLUT_KEY_HOME://sube la camara= baja el escenario			
			Modelo::getInstance()->getCamara().strafeUp(1);
			break;
		case GLUT_KEY_END:			
			Modelo::getInstance()->getCamara().strafeUp(-1);
			break;
		case GLUT_KEY_F1: 
			
			Modelo::getInstance()->getCamara().vistaAerea(Modelo::getInstance()->getMapa()->getAlto(),Modelo::getInstance()->getMapa()->getAncho());
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

	if(!texSuelo.cargarTGA(TEX_PATH_SUELO)) {
		printf("Error cargando textura\n");
		exit(-1);
	}
	if(!texPared.cargarTGA(TEX_PATH_PARED)) { 
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
	 		Modelo::getInstance()->setFinalizoJuego( true );
	 		ptrEnviar->enviarMensaje( new Key(KEY_ESCAPE) );
	 		ptrEnviar->join();
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


void  iniciarGraficos(int argc, char** argv)
{
	Modelo *modelo = Modelo::getInstance(); 
	std::cout<<"Obtiene mapa\n";
	glutInit( &argc, argv );	
	glutInitWindowSize( anchoVentana, altoVentana );
	std::cout<<"inicio windows\n";
	glutInitWindowPosition( 100, 100 );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow( "PACMAN 3D" );	
	glEnable(GL_TEXTURE_2D);

	cout<<"******inicio graficos"<<endl;
	initTexturas();
	modelo->getMutexMapa().lock();
	Mapa* mapa= modelo->getMapa();
	transformarParedes(mapa);
	modelo->getMutexMapa().unlock();
	//temp_setPosicionFantasma(); 
		
	glEnable( GL_DEPTH_TEST );	

	cout<<"comienza el loop"<<endl;
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

Socket* Cliente::getSocket()
{
	return skCliente;
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
		cout<<"logre conectar"<<endl;
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
void Cliente::comenzarJuego(int cantArg,char* argv[]) {
	
	//Se instancia el modelo. Singleton
	//Modelo::setInstance(cantArg,argv);

	//Comienza el juego...
	//Modelo::getInstance()->run();
	
	//Espera que finalice...
	//Modelo::getInstance()->join();
	this->enviarMensaje->run();
	ptrEnviar = this->enviarMensaje;
	std::cout<<"Entrar a iniciar graficos\n";
	iniciarGraficos(cantArg,argv);
	Modelo::getInstance()->setFinalizoJuego( true );
	this->enviarMensaje->join();
}

