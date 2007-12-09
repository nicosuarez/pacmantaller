#ifndef ICONO_H_
#define ICONO_H_

#include <libglademm/xml.h>
#include <gtkmm.h>
#include <iostream>
#include "tabla.h"
#include <vector>
#include "definiciones_editor.h"

class Icono: public Gtk::Image
{
	private:
		Gtk::Image Imagen;
		std::string pathImagen;
		std::string pathImagenSel;
		int idImagen;
		int cantRotaciones;
		int rotacion;
		static int ultimoClick;
		static int clickAnterior;
		static int ultimaMarca;
		static int marcaAnterior;
	public:
		Icono(int parId,std::string parPathImagen,std::string parPathImagenSel,int parCantRotaciones = 4);
		static int getUltimoClick(){ return ultimoClick;}
		static int getClickAnterior(){ return clickAnterior;}
		static int getUltimaMarca(){ return ultimaMarca;}
		static int getMarcaAnterior(){ return marcaAnterior;}
		int getRotacion(){ return rotacion;}
		void rotar();
		//Funciones de marca y click
		void marcar();
		void desMarcar();
		//Funciones para las distintas señales
		bool marca(GdkEventCrossing *E);
		bool click(GdkEventButton *E);
};

class BarraIconos
{
	private:
		std::vector<Icono*> vecIconos;
		std::vector<Gtk::EventBox*> vecEventos;
		Glib::RefPtr<Gnome::Glade::Xml> &refXml;
		Gtk::VBox *pCajaIconos;
		std::vector<std::string> vecPaths;
		std::vector<std::string> vecPathsSel;//Tiene las ismas imagenes que vecPaths pero seleccionadas
		Tabla **T;
		bool marcar(GdkEventCrossing *E);
		bool clickear(GdkEventButton *E);
	public:
		BarraIconos(Glib::RefPtr<Gnome::Glade::Xml> &parRefXml);
		void setearTabla(Tabla **parT);
		void activar();
		void desActivar();
};

#endif /*ICONO_H_*/
