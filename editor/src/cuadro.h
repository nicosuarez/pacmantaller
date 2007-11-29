#ifndef cuadro
#define cuadro

#include <gtkmm.h>
#include <iostream>
#include "tabla.h"

class Tabla;

class Cuadro: public Gtk::Image
{
	private:
		int fila;
		int columna;
		bool vacio;//true -> tiene la imagen de blanco
		Glib::RefPtr<Gdk::Pixbuf> pixOriginal;
		bool saturado;
	public:
		Cuadro(int fila,int columna);
		bool funcBoton(GdkEventButton *E);
		bool ocupado();
		void setImagen(std::string path);
		void setImagenMarca();
		void setImagenBlanco();
		bool funcCursorEntra(GdkEventCrossing *E);
		bool funcCursorSale(GdkEventCrossing *E);
		void saturar();
		void normalizar();
};

#endif
