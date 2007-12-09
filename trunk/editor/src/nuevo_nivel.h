#ifndef NUEVO_NIVEL_H_
#define NUEVO_NIVEL_H_

#include <libglademm/xml.h>
#include <gtkmm.h>
#include <sstream>
#include <list>
#include <iostream>
#include "definiciones_editor.h"


class NuevoNivel
{
	private:
		Gtk::Dialog *pDialogoNuevo;
		Glib::RefPtr<Gnome::Glade::Xml> &refXml;
		//Botones
		Gtk::Button *pBCancelar;
		//Combos
		Gtk::Combo *pComboFilas;
		Gtk::Combo *pComboColumnas;
		//Funciones para los botones
		void funcBCancelar();
		//Funciones para los combos
		void funcComboFilas();
		void funcComboColumnas();
		//Numeros de Filas y columnas seleccionadas
		int nroFila;
		int nroColumna;
		bool presCancelar;//Indica si fue preconado el boton cancelar
	public:
		NuevoNivel(Glib::RefPtr<Gnome::Glade::Xml> &refXmlAux);
		void correr();
		void getDatos(int &parCantFilas,int &parCantColumnas);
};

#endif /*NUEVO_NIVEL_H_*/
