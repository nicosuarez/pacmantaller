#ifndef MAPA_H_
#define MAPA_H_
#include "Grafo.h"

class Mapa
{
private:
	tGrafo *grafo;
	int ancho, alto;

public:
	Mapa( tGrafo *grafo, int ancho, int alto );
	
	Mapa();
		
	virtual ~Mapa();
	
	tGrafo* getGrafo();
	
	int getAncho()const;
	
	int getAlto()const;
	
	void setGrafo(tGrafo *grafo);
	
	void setAncho( int ancho );
	
	void setAlto( int alto );
};

#endif /*MAPA_H_*/
