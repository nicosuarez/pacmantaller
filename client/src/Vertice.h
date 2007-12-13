#ifndef VERTICE_H
#define VERTICE_H

#include "Coordenada.h"


class Vertice {

	private:		
		int idVertice;
		Coordenada posMapa;
		//int orientacion;

	public:
		Vertice();
		Vertice(int idVertice, Coordenada posMapa);
		~Vertice();
		Coordenada getCoordenada() { return posMapa;}
		int getIdVertice() { return idVertice;}
		//int getOrientacion() { return orientacion;}
		void setCoordenada(Coordenada posMapa); 
		void setIdVertice(int id) { idVertice = id;}
		//void setOrientacion(int orient) { orientacion = orient;}

};

#endif

