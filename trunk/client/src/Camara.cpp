#include "Camara.h"
#include <iostream>
using namespace std;


Camara::Camara():posOjo(0,0,0),posCentro(0,0,0),dirArriba(0,1,0){
	
}
Camara::Camara(Coordenada posOjo,Coordenada posCentro ,Coordenada dirArriba): posOjo(posOjo),posCentro(posCentro),dirArriba(dirArriba) {
		
	cSpeed = 0.5;//mientras mas alto mas velocidad de la camara: "mas rapido llego de una posicion a otra".
	rSpeed = 45;

}

Camara::~Camara(){

}


void Camara::setSpeed(float speed) {

	cSpeed = speed;		
}

void Camara::setOjo(Coordenada pos) {
	posOjo.x= pos.x;
	posOjo.y= pos.y;
	posOjo.z= pos.z;
}

void Camara::setCentro(Coordenada pos) {
	posCentro.x= pos.x;
	posCentro.y= pos.y;
	posCentro.z= pos.z;
}

void Camara::setArriba(Coordenada pos) {
	dirArriba.x= pos.x;
	dirArriba.y= pos.y;
	dirArriba.z= pos.z;
}

Coordenada Camara::getOjo() {
	return posOjo;
}

Coordenada Camara::getCentro() {
	return posCentro;
}

Coordenada Camara::getArriba() {
	return dirArriba;
}

//realiza calculo para mover la camara
int Camara::move(float dir) { //dir =1 ADELANTE  dir=-1 ATRAS

	Coordenada vDir;

	vDir = posCentro - posOjo;// x o y se haran cero
	
	//if (vDir.x<0) vDir.x = - vDir.x;
	//if (vDir.z<0) vDir.z = - vDir.z;
 	posOjo.x= posOjo.x  + vDir.x * (dir * cSpeed);
	posOjo.z= posOjo.z  + vDir.z * (dir * cSpeed);
	posCentro.x=posCentro.x + vDir.x * (dir * cSpeed);
	posCentro.z=posCentro.z + vDir.z * (dir * cSpeed);

	return 0;

}

int Camara::moverAdelante() {

	Coordenada vDir = posCentro - posOjo;// x o y se haran cero

 	posOjo.x= posOjo.x  + vDir.x * cSpeed;
	posOjo.z= posOjo.z  + vDir.z * cSpeed;
	posCentro.x=posCentro.x + vDir.x * cSpeed;
	posCentro.z=posCentro.z + vDir.z * cSpeed;

	return 0;
}

/*void Camara::rotate(float droot) {//dir =1 DERECHA  dir=-1 IZQUIERDA
	
	//posCentro.z=(float)(posOjo.z+ sin(rSpeed*droot )*vDir.x + cos(rSpeed*droot )*vDir.z);
	//posCentro.x=(float)(posOjo.x+ cos(rSpeed*droot )*vDir.x - sin(rSpeed*droot )*vDir.z);
	//Coordenada vDir = posCentro-posOjo;
	Coordenada vDir;
	vDir.x= posCentro.x - posOjo.x;
	vDir.z= posCentro.z - posOjo.z;
	if (vDir.x<0) vDir.x = - vDir.x;
	if (vDir.z<0) vDir.z = - vDir.z;
	cout<<"vDir "<<vDir.x<<" "<<vDir.z<<endl;	
	cout<<"ojo rotate x antes= "<<posOjo.x<<endl;
	cout<<"ojo rotate z antes= "<<posOjo.z<<endl;
	cout<<"Centro rotate x antes= "<<posCentro.x<<endl;
	cout<<"Centro rotate z antes= "<<posCentro.z<<endl;
	posCentro.x=posOjo.x + vDir.z * droot;
	posCentro.z=posOjo.z - vDir.x * droot;
	cout<<"Centro rotate x= "<<posCentro.x<<endl;
	cout<<"Centro rotate z= "<<posCentro.z<<endl<<endl;

}
*/

void Camara::moverIzq() {
		
	Coordenada vDir=posCentro-posOjo;

	if (vDir.z==0) {
		posCentro.x=posOjo.x - vDir.z;
		posCentro.z=posOjo.z - vDir.x;
	}
	else {
		posCentro.x=posOjo.x + vDir.z;
		posCentro.z=posOjo.z + vDir.x;
	}
	
}

void Camara::moverDer() {
		
	Coordenada vDir=posCentro-posOjo;

	if (vDir.z==0) {
		posCentro.x=posOjo.x + vDir.z;
		posCentro.z=posOjo.z + vDir.x;
	}
	else {
		posCentro.x=posOjo.x - vDir.z;
		posCentro.z=posOjo.z - vDir.x;
	}	
}


void Camara::rotateUp(float droot) {

	posCentro.y=posCentro.y + rSpeed*1*droot;
}


void Camara::strafeUp(float droot) {	

	posOjo.y=posOjo.y + cSpeed*0.5*droot;
	posCentro.y=posOjo.y;
}


void Camara::update() {
	
	glLoadIdentity();//antes que nada se inicializa la matriz a la identidad
	//gluLookAt define dónde esta el observador, hacia donde esta mirando y cual es el eje que nos indica la dirección hacia arriba.
//gluPerspective(45,(GLfloat)width/(GLfloat)height,  0.01, 100);
	//gluLookAt(camera[0],camera[1],camera[2],target[0],target[1],target[2],0,1,0);

	gluLookAt(posOjo.x,posOjo.y,posOjo.z,posCentro.x,posCentro.y,posCentro.z,dirArriba.x,dirArriba.y,dirArriba.z);

}

void Camara::vistaAerea() {	
	posOjo.x=10;
	posOjo.y=25;
	posOjo.z=-10;
	posCentro.x=10;
	posCentro.y=4;
	posCentro.z=-10;
	dirArriba.x=1;
	dirArriba.y=0;
	dirArriba.z=0;
		
}

