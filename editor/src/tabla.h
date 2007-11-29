#ifndef tabla_h
#define tabla_h

#include <gtkmm.h>
#include "cuadro.h"
#include "definiciones_editor.h"
#include <vector>
#include <map>
#include "cordenada.h"
#include "insertar_imag.h"
#include <list>

class Cuadro;

class RegElemento
{
	private:
		int nroImag;
		int rot;
		int filaInicial;
		int columnaInicial;
	public:
		RegElemento(int parNro,int parRot,int parFila,int parColumna):nroImag(parNro),rot(parRot),filaInicial(parFila),columnaInicial(parColumna){}
		void get(int &parNro,int &parRot,int &parFila,int &parColumna)
		{
			parNro = nroImag;
			parRot = rot;
			parFila = filaInicial;
			parColumna = columnaInicial;
		}
		bool operator==(const RegElemento& R) const
		{
			return ( (nroImag ==R.nroImag) && (rot ==R.rot) && (filaInicial ==R.filaInicial) && (columnaInicial ==R.columnaInicial) );
		}
};

class Tabla
{
	private:
		Gtk::Table Matriz;
		static int nroImg;
		static int rot;
		static int cantFilas;
		static int cantColumnas;
		static int filaInicial;
		static int columnaInicial;
		static std::map<Cordenada,Cuadro*> mapCuadros;
		static TipoModo modo;
		static void* In;
		static std::list<RegElemento> listaElementos;//Contiene nroElemento,rot,filaInicial,columnaInicial
		static std::list<RegElemento> listaModificadores;
		static void crearImg();
	public:
		Tabla(int cantFilas,int cantColumnas);
		Gtk::Table& getMatriz();
		void setInfo(int nroBoton,int rot);
		void setModo(TipoModo parModo);
		static void dibujar(int fila,int columna);
		static void marcar(int fila,int columna);
		static void desMarcar(int fila,int columna);
};

#endif
