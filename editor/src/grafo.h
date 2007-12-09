#ifndef GRAFO_H_
#define GRAFO_H_

#include <map>
#include <list>
#include <iostream>
#include <sstream>
#include "definiciones_editor.h"

class RegArista 
{
	private:
		int idArista;
		int idV1;
		int idV2;
	public:
		RegArista(int parIdA,int parIdV1,int parIdV2):idArista(parIdA),idV1(parIdV1),idV2(parIdV2){}
		void get(int &parIdA,int &parIdV1,int &parIdV2)
		{
			parIdA = idArista;
			parIdV1 = idV1;
			parIdV2 = idV2;
		}
		bool operator==(const RegArista &R) const
		{
			return (idArista == R.idArista);
		}
		RegArista& operator=(const RegArista &R)
		{
			idArista = R.idArista;
			idV1 = R.idV1;
			idV2 = R.idV2;
			return *this;
		}
		bool operator<(const RegArista &R) const
		{
			return (idArista < R.idArista);
		}
};

class Vertice
{
	private:
		int id;
		bool oeste;
		bool este;
		bool norte;
		bool sur;
		bool conector;
	public:
		Vertice(bool parOeste,bool parEste,bool parNorte,bool parSur,bool parConector=false);
		void setId(int parId);
		int getId();
		//Indicadores de conexion existente
		bool conexionEste();
		bool conexionOeste();
		bool conexionNorte();
		bool conexionSur();
		bool esPortal();
};

class Grafo
{
	private:
		std::map<int,Vertice*> mapVertices;
		std::list<RegArista> listaDeAristas; //Con rima y todo
		int cantFilas;
		int cantColumnas;
	public:
		Grafo (int nroFilas,int nroColumnas);
		int agregarVertice(Vertice *V,int fila,int columna);
		void eliminarVertice(int fila,int columna);
		std::list<RegArista> getListaDeAristas(); //Sigue la rima je!
		bool grafoValido(std::string &mensajeError);
		~Grafo();
		void imprimirGrafo();//TODO
		
};

#endif /*GRAFO_H_*/
