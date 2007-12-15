#ifndef COORDENADA_H_
#define COORDENADA_H_

#include "Posicion.h"
#include "ActualizarJuego.h"
#include <math.h>

class Coordenada
{
private:
	double x;
	double y;
public:

	Coordenada();
	Coordenada(const Coordenada& coord);
	Coordenada(double x,double y);
	double getX(){return x;};
	double getY(){return y;};
	void setX(double x){this->x=x;};
	void setY(double y){this->y=y;};
	void setCoordenada(double x,double y);
	static Coordenada transformarPosicion(Posicion* posicion,Mapa* mapa);
	static double calcularDistancia(Posicion* pos1,Posicion* pos2,Mapa* mapa);
	
};

#endif /*COORDENADA_H_*/
