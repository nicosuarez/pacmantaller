#ifndef editor_mundos_h
#define editor_mundos_h

#include <libglademm/xml.h>
#include <gtkmm.h>
#include <iostream>
#include "nuevo_nivel.h"
#include "tabla.h"
#include <vector>
#include "icono.h"
#include <sstream>

class Editor
{
	private:
		Glib::RefPtr<Gnome::Glade::Xml> &refXml;
		//Ventana
		Gtk::Window *pVEditor;
		//Elementos del menu
		Gtk::MenuItem *pItemNuevo;
		Gtk::MenuItem *pItemCargar;
		Gtk::MenuItem *pItemGuardar;
		Gtk::MenuItem *pItemSalir;
		Gtk::MenuItem *pItemManual;
		Gtk::MenuItem *pItemAcerca;
		//Botones de Insertar y Quitar
		Gtk::RadioToolButton *pBotonAgregar;
		Gtk::RadioToolButton *pBotonQuitar;
		//Funciones para estos botones
		void funcBotonAgregar();
		void funcBotonQuitar();
		//Ventana de Nuevo Nivel
		NuevoNivel N;
		//Caja de Iconos
		BarraIconos B;
		//Informacion del nivel
		int nroNivel;
		//Variable de Modo
		TipoModo modo;
		//Funciones para los elemntos del menu
		void funcItemNuevo();
		void funcItemCargar();
		void funcItemGuardar();
		void funcItemSalir();
		void funcItemManual();
		void funcItemAcerca();
	
		Gtk::Label *pLabelInfo;
		
		//Caja Horizontal qie contiene la tabla e indicaciones
		Gtk::VBox *pCajaVertical;
		
		

		//Matriz con las celdas del mapa y los labels que completan
		Tabla *T;
		
		//Funcion para cuando se preciona el borton "Aceptar" de la ventana de Nuevo Nivel
		static void funcAceptar(int nFila,int nColumna,void *pObjetoEditor);

	public:
		Editor(Glib::RefPtr<Gnome::Glade::Xml> &refXmlAux);
		void correr();
		
};

#endif
