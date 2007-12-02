#ifndef MODELO_H_
#define MODELO_H_
#include <iostream>
#include <list>
#include "Elemento.h"

class Modelo
{
private:
	static Modelo* pModelo;
	int id;
	int puntuacion;
	bool finalizoJuego;
	bool finalizoNivel;
	int **ph; //Matriz que representa las paredes horizontales del mapa
	int **pv; //Matriz que representa las paredes verticales del mapa
	std::list<Elemento*> *elementos;
	Modelo();
public:
	
	virtual ~Modelo();
	
	static Modelo* getInstance();
	
	void setid( int newid );
	
	void setPuntuacion( int newPuntuacion );
	
	void setFinalizoJuego( bool finalizo );
	
	void setFinalizoNivel( bool finalizo );
	
	void setMatrices( int **ph, int **pv );
	
	void setElementos( std::list<Elemento*> *elementos );
	
	int getid()const;
	
	int getPuntuacion()const;
	
	bool getFinalizoJuego()const;
	
	bool getFinalizoNivel()const;
	
	int** getph()const;
	
	int** getpv()const;
	
	std::list<Elemento*>* getElementos()const;
};

#endif /*MODELO_H_*/
