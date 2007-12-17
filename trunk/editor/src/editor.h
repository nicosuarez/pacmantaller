#ifndef EDITOR_H_
#define EDITOR_H_

#include <libglademm/xml.h>
#include <gtkmm.h>
#include <iostream>
#include "nuevo_nivel.h"
#include "tabla.h"
#include <vector>
#include "icono.h"
#include <sstream>
#include "xml_parser.h"
#include "abrir_nivel.h"

class Editor
{
	private:
		Glib::RefPtr<Gnome::Glade::Xml> &refXml;
		//Ventana
		Gtk::Window *pVEditor;
		//Barra de Modo
		Gtk::Toolbar *pBarraModo;
		//Elementos del menu
		Gtk::MenuItem *pItemNuevo;
		Gtk::MenuItem *pItemCargar;
		Gtk::MenuItem *pItemGuardar;
		Gtk::MenuItem *pItemSalir;
		Gtk::MenuItem *pItemManual;
		Gtk::MenuItem *pItemAcerca;
		Gtk::MenuItem *pItemCerrar;
		//Dialogo de Guardar y error
		Gtk::Dialog *pDialogoGuardar;
		Gtk::Dialog *pDialogoEditorError;
		Gtk::Label *pLabelEditorError;
		//Botones de Insertar y Quitar
		Gtk::RadioToolButton *pBotonAgregar;
		Gtk::RadioToolButton *pBotonQuitar;
		//Funciones para estos botones
		void funcBotonAgregar();
		void funcBotonQuitar();
		//Funciones para los elemntos del menu
		void funcItemNuevo();
		void funcItemCargar();
		void funcItemGuardar();
		void funcItemSalir();
		void funcItemManual();
		void funcItemAcerca();
		void funcItemCerrar();
		//Ventana de Nuevo Nivel
		NuevoNivel N;
		AbrirNivel A;
		Gtk::Label *pLabelInfo;
		//Caja de Iconos
		BarraIconos B;
		//Informacion del nivel
		int nroNivel;
		//Variable de Modo
		TipoModo modo;
		//Caja Horizontal qie contiene la tabla e indicaciones
		Gtk::VBox *pCajaVertical;
		//Matriz con las celdas del mapa y los labels que completan
		Tabla *T;
		
		//Funcion para crear la tabla del Nuevo Nivel
		void crearTabla(int nFila,int nColumna);

		//Parser para guardar y abrir archivos
		XmlParser Parser;
	public:
		Editor(Glib::RefPtr<Gnome::Glade::Xml> &refXmlAux);
		void correr();
		~Editor();
		
};

#endif /*EDITOR_H_*/
