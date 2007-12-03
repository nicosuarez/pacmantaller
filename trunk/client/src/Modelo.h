#ifndef MODELO_H_
#define MODELO_H_
#include <iostream>
#include <list>
#include "Elemento.h"
#include "Personaje.h"

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
	std::list<Elemento*> elementos;
	std::list<Personaje*> personajes;
	Modelo();
public:
	
	virtual ~Modelo();
	
	static Modelo* getInstance();
	
	void setid( int newid );
	
	void setPuntuacion( int newPuntuacion );
	
	void setFinalizoJuego( bool finalizo );
	
	void setFinalizoNivel( bool finalizo );
	
	void setMatrices( int **ph, int **pv );
	
	int getid()const;
	
	int getPuntuacion()const;
	
	bool getFinalizoJuego()const;
	
	bool getFinalizoNivel()const;
	
	int** getph()const;
	
	int** getpv()const;
	
	std::list<Elemento*>* getElementos();
	
	std::list<Personaje*>* getPersonajes();
};

#endif /*MODELO_H_*/
