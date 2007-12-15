#include "Coordenada.h"

Coordenada::Coordenada()
{
	this->x=0;
	this->y=0;
}

Coordenada::Coordenada(const Coordenada& coord)
{
	this->x = coord.x;
	this->y = coord.y;
}

Coordenada::Coordenada(double x,double y)
{
	this->setX(x);
	this->setY(y);
}

void Coordenada::setCoordenada(double x,double y)
{
	this->setX(x);
	this->setY(y);
}

Coordenada Coordenada::transformarPosicion(Posicion* posicion,Mapa* mapa)
{
	double x=0;
	double y=0;
	int ancho=mapa->getAncho();
	int alto=mapa->getAlto();
	int idVertice=posicion->getVertice();
	int numFila=idVertice/ancho;
	int posArista= posicion->getArista();
	
	tArco* arcoActual = NULL;//ActualizarJuego::getAristaActual(posicion);
	
	int oriActual = arcoActual->getElemento();
	
	x+=0.5;
	y+=0.5;
	
	switch(oriActual)
	{
		case Norte:
			y+=numFila-posArista/FIN_ARISTA; //Ver
			if(y<0)y+=ancho;
			x+=idVertice-(numFila*ancho);
			break;
		case Este:
			x+=idVertice + (posArista/FIN_ARISTA) - (numFila*ancho);
			if(x>ancho)x-=ancho;
			y+=numFila;
			break;
		case Sur:
			y+=numFila+(1-posArista/FIN_ARISTA); //Ver
			if(y>alto)y-=alto;
			x+=idVertice-(numFila*ancho);
			break;
		case Oeste:
			x+=(idVertice-1) + (posArista/FIN_ARISTA) - (numFila*ancho);
			if(x<0) x += ancho ;
			y+=numFila;
			break;
	}
	Coordenada coord(x,y);
	return coord;
}

double Coordenada::calcularDistancia(Posicion* pos1,Posicion* pos2,Mapa* mapa)
{
	Coordenada coord1 = Coordenada::transformarPosicion(pos1,mapa);
	Coordenada coord2 = Coordenada::transformarPosicion(pos2,mapa);
	
	double dX = coord1.getX() - coord2.getX();
	double dY = coord1.getY() - coord2.getY();
	
	double dist = pow(dX,2)+pow(dY,2);
	return sqrt(dist);
}

