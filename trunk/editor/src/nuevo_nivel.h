#ifndef nuevo_nivel_h
#define nuevo_nivel_h

#include <libglademm/xml.h>
#include <gtkmm.h>
#include <sstream>
#include <list>
#include <iostream>
#include "definiciones_editor.h"


class Editor;

class NuevoNivel
{
	private:
		Gtk::Window *pVNuevo;
		Glib::RefPtr<Gnome::Glade::Xml> &refXml;
		//Botones
		Gtk::Button *pBAceptar;
		Gtk::Button *pBCancelar;
		//Combos
		Gtk::Combo *pComboFilas;
		Gtk::Combo *pComboColumnas;
		//Funciones para los botones
		void funcBAceptar();
		void funcBCancelar();
		//Funciones para los combos
		void funcComboFilas();
		void funcComboColumnas();
		//Numeros de Filas y columnas seleccionadas
		int nroFila;
		int nroColumna;
		//Funcion que se ejecuta en funcBAceptar
		void (*pFuncionAceptar)(int,int,void *pE);
		void *pObjetoEditor;
	public:
		NuevoNivel(Glib::RefPtr<Gnome::Glade::Xml> &refXmlAux);
		void mostrar( void (*pFuncionAceptar)(int,int,void *pE) ,void *pObjetoEditor);
};

#endif
