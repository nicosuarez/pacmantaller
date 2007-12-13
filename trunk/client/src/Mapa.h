#ifndef MAPA_H_
#define MAPA_H_
#include <iostream>

class Mapa
{
private:
	int **ph; //Matriz que representa las paredes horizontales del mapa
	int **pv; //Matriz que representa las paredes verticales del mapa
	int ancho, alto;
	
public:
	
	Mapa( int ancho, int alto );
	
	Mapa( int **ph, int **pv, int ancho, int alto );
	
	virtual ~Mapa();
	
	int** getph();
	
	int** getpv();
	
	int getAncho()const;
	
	int getAlto()const;
	
	void setph(int **newph);
	
	void setpv(int **newpv);
	
	void setAncho( int ancho );
	
	void setAlto( int alto );
};

#endif /*MAPA_H_*/
