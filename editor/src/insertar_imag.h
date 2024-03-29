#ifndef INSERTAR_IMAG_H_
#define INSERTAR_IMAG_H_

#include "cuadro.h"
#include "cordenada.h"
#include "definiciones_editor.h"
#include <gtkmm.h>
#include <map>
#include <list>
#include "grafo.h"

class Cuadro;

class InsertarImag
{
	protected:
		std::map<Cordenada,Cuadro*> &mapCuadros;
		int cantFilas;
		int cantColumnas;
		int rot;
		bool permiso;
		//Funcion que dice si se puede dibujar
		bool valido(bool fila,int posInicial,int posFija,int cuanto);
		void colocarImagen(Cordenada &C,TipoOperacion op,std::string &archivo);
		int insertarVertices(std::list<Cordenada> &listaCordenadas,std::list<Vertice*> &listaVertices,Grafo &G);
	public:
		InsertarImag(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot);
		void darPermiso();
		bool getPermiso();
		virtual void insertar(TipoOperacion op,int fila,int columna) = 0;
		virtual std::list<Cordenada> getListaVertices(int fila,int columna) = 0;
		virtual int actualizarGrafo(int fila,int columna,Grafo &G) = 0;
		virtual ~InsertarImag(){}
};

//Clases Derivadas

class Imag0:public InsertarImag
{
	public:
		Imag0(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot);
		void insertar(TipoOperacion op,int fila,int columna);
		std::list<Cordenada> getListaVertices(int fila,int columna);
		int actualizarGrafo(int fila,int columna,Grafo &G);
};

class Imag1:public InsertarImag
{
	private:
		void colocarParteVertical(TipoOperacion op,int fila,int columna);
		void colocarParteHorizontal(TipoOperacion op,int fila,int columna);
		void colocarConector(TipoOperacion op,int fila,int columna);
		void insertarRot0(TipoOperacion op,int fila,int columna);
		void insertarRot1(TipoOperacion op,int fila,int columna);
		void insertarRot2(TipoOperacion op,int fila,int columna);
		void insertarRot3(TipoOperacion op,int fila,int columna);
	public:
		Imag1(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot);
		void insertar(TipoOperacion op,int fila,int columna);
		std::list<Cordenada> getListaVertices(int fila,int columna);
		int actualizarGrafo(int fila,int columna,Grafo &G);
};

class Imag2:public InsertarImag
{
	private:
		void colocarTramoVertical(TipoOperacion op,int fila,int columna,std::string medio);
		void colocarTramoHorizontal(TipoOperacion op,int fila,int columna,std::string medio);
		void colocarPunto(TipoOperacion op,int fila,int columna,std::string archivo);
		void insertarRot0(TipoOperacion op,int fila,int columna);
		void insertarRot1(TipoOperacion op,int fila,int columna);
		void insertarRot2(TipoOperacion op,int fila,int columna);
		void insertarRot3(TipoOperacion op,int fila,int columna);
	public:
		Imag2(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot);
		void insertar(TipoOperacion op,int fila,int columna);
		std::list<Cordenada> getListaVertices(int fila,int columna);
		int actualizarGrafo(int fila,int columna,Grafo &G);
};

class Imag3:public InsertarImag
{
	public:
		Imag3(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot);
		void insertar(TipoOperacion op,int fila,int columna);
		std::list<Cordenada> getListaVertices(int fila,int columna);
		int actualizarGrafo(int fila,int columna,Grafo &G);
};

class Imag4:public InsertarImag
{
	private:
		void insertarRot0(TipoOperacion op,int fila,int columna);
		void insertarRot1(TipoOperacion op,int fila,int columna);
		void insertarRot2(TipoOperacion op,int fila,int columna);
		void insertarRot3(TipoOperacion op,int fila,int columna);
	public:
		Imag4(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot);
		void insertar(TipoOperacion op,int fila,int columna);
		std::list<Cordenada> getListaVertices(int fila,int columna);
		int actualizarGrafo(int fila,int columna,Grafo &G);
};

class Imag5:public InsertarImag
{
	private:
		void colocarTramoVertical(TipoOperacion op,int fila,int columna);
		void colocarTramoHorizontal(TipoOperacion op,int fila,int columna);
		void colocarPasaje(TipoOperacion op,int fila,int columna,std::string archivo);
		void insertarRot0y2(TipoOperacion op,int fila,int columna);
		void insertarRot1y3(TipoOperacion op,int fila,int columna);
	public:
		Imag5(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot);
		void insertar(TipoOperacion op,int fila,int columna);
		std::list<Cordenada> getListaVertices(int fila,int columna);
		int actualizarGrafo(int fila,int columna,Grafo &G);
};

class Imag6:public InsertarImag
{
	public:
		Imag6(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot);
		void insertar(TipoOperacion op,int fila,int columna);
		std::list<Cordenada> getListaVertices(int fila,int columna);
		int actualizarGrafo(int fila,int columna,Grafo &G){return EXITO;}
};

class Imag7:public InsertarImag
{
	public:
		Imag7(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot);
		void insertar(TipoOperacion op,int fila,int columna);
		std::list<Cordenada> getListaVertices(int fila,int columna);
		int actualizarGrafo(int fila,int columna,Grafo &G){return EXITO;}
};

class Imag8:public InsertarImag
{
	public:
		Imag8(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot);
		void insertar(TipoOperacion op,int fila,int columna);
		std::list<Cordenada> getListaVertices(int fila,int columna);
		int actualizarGrafo(int fila,int columna,Grafo &G){return EXITO;}
};

#endif /*INSERTAR_IMAG_H_*/
