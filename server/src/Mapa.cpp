#include "Mapa.h"

Mapa::Mapa( tGrafo *grafo, int ancho, int alto )
{
	this->grafo = grafo;
	this->ancho = ancho;
	this->alto = alto;
}

Mapa::Mapa()
{
	this->grafo = new tGrafo;
	this->ancho = 0;
	this->alto = 0;
}

Mapa::~Mapa()
{
	delete grafo;
}

tGrafo* Mapa::getGrafo()
{
	return grafo;
}

int Mapa::getAncho()const
{
	return ancho;
}

int Mapa::getAlto()const
{
	return alto;
}

void Mapa::setGrafo(tGrafo *grafo)
{
	this->grafo = grafo;
}

void Mapa::setAncho( int ancho )
{
	this->ancho = ancho;
}

void Mapa::setAlto( int alto )
{
	this->alto = alto;
}
