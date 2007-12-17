#ifndef TABLA_H_
#define TABLA_H_

#include <gtkmm.h>
#include "cuadro.h"
#include "definiciones_editor.h"
#include <vector>
#include <map>
#include "cordenada.h"
#include "insertar_imag.h"
#include <list>
#include "grafo.h"
#include <libglademm.h>

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
		Grafo G;
		Glib::RefPtr<Gnome::Glade::Xml> &refXml;
		Gtk::Dialog *pDialogoError;
		Gtk::Label *pLabelError;
		int nroImg;
		int rot;
		int cantFilas;
		int cantColumnas;
		int filaInicial;
		int columnaInicial;
		std::map<Cordenada,Cuadro*> mapCuadros;
		TipoModo modo;
		void* In;
		std::list<RegElemento> listaElementos;//Contiene nroElemento,rot,filaInicial,columnaInicial
		std::list<RegElemento> listaModificadores;
		void crearImg();
		//Con respecto a los modificadores
		bool pacman;
		bool casa;
		bool pasoValido(int f,int c,std::string &error);
	public:
		Tabla(int cantFilas,int cantColumnas,Glib::RefPtr<Gnome::Glade::Xml> &parRefXml);
		Gtk::Table& getMatriz();
		void setInfo(int nroBoton,int rot);
		void setModo(TipoModo parModo);
		void dibujar(int fila,int columna);
		void marcar(int fila,int columna);
		void desMarcar(int fila,int columna);
		void getTamanio(int &parCantFilas,int &parCantColumnas);
		Grafo& getGrafo();
		std::list<RegElemento>& getListaModificadores();
		std::list<RegElemento>& getListaElementos();
		std::list<Cordenada> getVerticesCasa(std::string &orientacion);
		void setInfoAbrir(std::list<RegElemento> &listaEle,std::list<RegElemento> &listaMod);
		bool tablaValida(std::string &mensajeError);
		~Tabla();
};

#endif /*TABLA_H_*/
