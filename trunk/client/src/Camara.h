#ifndef CAMARA_H
#define CAMARA_H

#include "Coordenada.h"


class Camara {

	private:				
		Coordenada posOjo;
		Coordenada posCentro;
		Coordenada dirArriba;
		float cSpeed,rSpeed;
		
	public: 

		Camara();
		Camara(Coordenada posOjo,Coordenada posCentro ,Coordenada dirArriba);
		~Camara();		
		
		void setOjo(Coordenada pos); 
		void setCentro(Coordenada pos);
		void setArriba(Coordenada pos); 
		Coordenada getOjo();
		Coordenada getCentro();
		Coordenada getArriba(); 

		//movimiento de la camara 
		int move(float speed);
		void rotate(float speed);		
		void rotateUp(float droot);
		void strafeUp(float droot); 
	 	int moverAdelante(); 
		void moverIzq(); 
		void moverDer(); 

		
		void update();  // actualiza glutLookAt(..) Con los parametros de la camara
		void setSpeed(float speed);
};	

#endif
