#include "cuadro.h"


Cuadro::Cuadro(int fila,int columna):Gtk::Image(PATH_BLANCO)
{
	Cuadro::fila = fila;
	Cuadro::columna = columna;
	vacio = true;
	saturado = false;
}

bool Cuadro::funcBoton(GdkEventButton *E)
{
	//Responde al click del mouse
	std::cout << "Se presiono el cuadro de: (flia,columna)" << fila << " " << columna << std::endl; //TODO
	Tabla::dibujar(fila,columna);
	return false;
}

bool Cuadro::ocupado()
{
	return (!vacio);
}

void Cuadro::setImagen(std::string path)
{
	vacio = false;
	clear();
	set(path);
	show();
}

void Cuadro::setImagenBlanco()
{
	clear();
	set(PATH_BLANCO);
	show();
	vacio = true;
	saturado = false;
}

void Cuadro::setImagenMarca()
{
	clear();
	set(PATH_NEGRO);
	show();
}

bool Cuadro::funcCursorEntra(GdkEventCrossing *E)
{
	Tabla::marcar(fila,columna);
	return true;
}

bool Cuadro::funcCursorSale(GdkEventCrossing *E)
{
	Tabla::desMarcar(fila,columna);
	return true;
}

void Cuadro::saturar()
{
	//Guardo el original
	if (!saturado)
	{
		pixOriginal = (get_pixbuf())-> copy();
		Glib::RefPtr<Gdk::Pixbuf> pixCambio = get_pixbuf();
		get_pixbuf() -> saturate_and_pixelate(pixCambio,0,false);
		clear();
		set(pixCambio);
		saturado = true;
	}
}

void Cuadro::normalizar()
{
	//---TODO-----------
	/*Glib::RefPtr<Gdk::Pixbuf> pixCambio = get_pixbuf();
	get_pixbuf() -> saturate_and_pixelate(pixCambio,15,true);
	clear();
	set(pixCambio);*/
	//----TODO------------
	clear();
	set(pixOriginal);
	saturado = false;
}
