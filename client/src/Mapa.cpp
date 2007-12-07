#include "Mapa.h"

Mapa::Mapa( int ancho, int alto )
{
	this->ph = NULL;
	this->pv = NULL;
	this->ancho = ancho;
	this->alto = alto;
}

Mapa::Mapa( int **ph, int **pv, int ancho, int alto )
{
	this->ph = ph;
	this->pv = pv;
	this->ancho = ancho;
	this->alto = alto;
}

Mapa::~Mapa()
{
	//Si ph es dsitinto de NULL elimino la matriz que estaba almacenada
	if( ph != NULL )
	{
		//Elimino la memoria alocada de las columnas
		for(int i=0; i<alto+1; i++ )
			delete []ph[i];
		//Elimino la memoria alocada para las filas
		delete []ph;
	}
	
	//Si pv es dsitinto de NULL elimino la matriz que estaba almacenada
	if( pv != NULL )
	{
		//Elimino la memoria alocada de las columnas
		for(int i=0; i<alto; i++ )
			delete []pv[i];
		//Elimino la memoria alocada para las filas
		delete []pv;
	}
}

int Mapa::getAncho()const
{
	return ancho;
}

int Mapa::getAlto()const
{
	return alto;
}

int** Mapa::getph()
{
	return this->ph;
}

int** Mapa::getpv()
{
	return this->pv;
}

void Mapa::setAncho( int ancho )
{
	this->ancho = ancho;
}

void Mapa::setAlto( int alto )
{
	this->alto = alto;
}

void Mapa::setph(int **newph)
{
	//Asigno la nueva matriz
	ph = newph;
}

void Mapa::setpv(int **newpv)
{
	//Asigno la nueva matriz
	pv = newpv;
}

