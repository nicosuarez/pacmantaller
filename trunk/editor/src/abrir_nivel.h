#ifndef ABRIR_NIVEL_H_
#define ABRIR_NIVEL_H_

#include <gtkmm.h>
#include <libglademm/xml.h>
#include <sstream>
#include "definiciones_editor.h"

class AbrirNivel
{
	private:
		int nroSel;
		Gtk::Dialog *pDialogoAbrir;
		Gtk::Combo *pComboAbrir;
		Gtk::Button *pBotonCancelarAbrir;
		Glib::RefPtr<Gnome::Glade::Xml> &refXml;
		//Funcion para el boton de cancelar
		void funcBotonCancelar();
		bool presCancelar; //indica si se preciono el boton de "Cancelar"
	public:
		AbrirNivel(Glib::RefPtr<Gnome::Glade::Xml> &parRefXml);
		void correr(int nroMaximo);
		int getNroSel();
};

#endif /*ABRIR_NIVEL_H_*/
