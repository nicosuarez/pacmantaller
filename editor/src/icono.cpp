#include "icono.h"
//Clase Icono
//-----------
int Icono::ultimoClick = -2;
int Icono::clickAnterior = -2;
int Icono::ultimaMarca = -1;
int Icono::marcaAnterior = -1;

Icono::Icono(int parId,std::string parPathImagen,std::string parPathImagenSel,int parCantRotaciones):Gtk::Image(parPathImagen),pathImagen(parPathImagen),pathImagenSel(parPathImagenSel),cantRotaciones(parCantRotaciones),idImagen(parId)
{
	rotacion = 0;
}
//Funciones para las señales
bool Icono::marca(GdkEventCrossing *E)
{
	marcaAnterior = ultimaMarca;
	ultimaMarca = idImagen;
	return false;
}

void Icono::marcar()
{
	//(get_pixbuf()) -> saturate_and_pixelate(get_pixbuf(),20,false);
	//set(get_pixbuf());
	clear();
	set(pathImagenSel);
	for ( int x = 0 ; x < rotacion ; x++ )//Si la imagen a marcar estaba rotada, tengo que rotar la nueva
		set ( (get_pixbuf()) -> rotate_simple(Gdk::PIXBUF_ROTATE_CLOCKWISE  ) );
	show();
}
void Icono::desMarcar()
{
	clear();
	set(pathImagen);
	for ( int x = 0 ; x < rotacion ; x++ )//Al poner la imagen desmarcada, debo mantener la rotacion
		set ( (get_pixbuf()) -> rotate_simple(Gdk::PIXBUF_ROTATE_CLOCKWISE  ) );
	show();
}

bool Icono::click(GdkEventButton *E)
{
	clickAnterior = ultimoClick;
	ultimoClick = idImagen;
	
	return false;
}

void Icono::rotar()
{
	//Rota 90 grados
	if (cantRotaciones != 0)
	{
		set ( (get_pixbuf()) -> rotate_simple(Gdk::PIXBUF_ROTATE_CLOCKWISE  ) );
		rotacion++;
		if (rotacion == cantRotaciones)
			rotacion = 0;
	}
}

//-------------------------------------------------------------------------------

//Clase BaraaIconos
//-----------------
void BarraIconos::setearTabla(Tabla **parT)
{
	T = parT;
}

BarraIconos::BarraIconos(Glib::RefPtr<Gnome::Glade::Xml> &parRefXml):refXml(parRefXml),vecPaths(CANT_IMAGENES),vecPathsSel(CANT_IMAGENES)
{
	refXml -> get_widget("cajaIconos",pCajaIconos);

	//Ponemos en el vector de paths los paths de las imagenes
	vecPaths[0] = PATH_IMG1;
	vecPathsSel[0] = PATH_IMG1_SEL;
	vecPaths[1] = PATH_IMG2;
	vecPathsSel[1] = PATH_IMG2_SEL;
	vecPaths[2] = PATH_IMG3;
	vecPathsSel[2] = PATH_IMG3_SEL;
	vecPaths[3] = PATH_IMG4;
	vecPathsSel[3] = PATH_IMG4_SEL;
	vecPaths[4] = PATH_IMG5;
	vecPathsSel[4] = PATH_IMG5_SEL;
	vecPaths[5] = PATH_IMG6;
	vecPathsSel[5] = PATH_IMG6_SEL;
	vecPaths[6] = PATH_IMG7;
	vecPathsSel[6] = PATH_IMG7_SEL;
	vecPaths[7] = PATH_IMG8;
	vecPathsSel[7] = PATH_IMG8_SEL;
	vecPaths[8] = PATH_IMG9;
	vecPathsSel[8] = PATH_IMG9_SEL;

	//Creo los Iconos y los inserto en la caja de iconos
	for (int x = 0 ; x < CANT_IMAGENES ; x++ )
	{
		Gtk::EventBox *E = new Gtk::EventBox();
		E -> set_visible_window(false);
		E -> set_events(Gdk::ALL_EVENTS_MASK);
		vecEventos.push_back(E);
		if (x == 0) //La imagen 1 solo tiene dos rotaciones
			vecIconos.push_back(new Icono(x,vecPaths[x],vecPathsSel[x],2));
		else
			if ( (x == 3) || (x >= 6) ) //La imagen 3 y de la 6 para adelante no se rotan
				vecIconos.push_back(new Icono(x,vecPaths[x],vecPathsSel[x],0));
			else
				vecIconos.push_back(new Icono(x,vecPaths[x],vecPathsSel[x]));
		//Cursor encima
		E -> signal_enter_notify_event().connect( sigc::mem_fun(*vecIconos[x],&Icono::marca) );
		E -> signal_enter_notify_event().connect( sigc::mem_fun(*this,&BarraIconos::marcar) );
		//Click
		E -> signal_button_press_event().connect( sigc::mem_fun(*vecIconos[x],&Icono::click) );
		E -> signal_button_press_event().connect( sigc::mem_fun(*this,&BarraIconos::clickear) );

		//( vecIconos[x] -> get_pixbuf() ) -> saturate_and_pixelate(vecIconos[x] -> get_pixbuf(),-10,false);//TODO

		E -> add(*vecIconos[x]);
		pCajaIconos -> pack_start(*E);
		
		E -> show();
		vecIconos[x] -> show();
	}
}

bool BarraIconos::marcar(GdkEventCrossing *E)
{
	int marcaAnterior = Icono::getMarcaAnterior();
	int ultimaMarca =  Icono::getUltimaMarca();
	int ultimoClick = Icono::getUltimoClick();

	//Desmarcamos el elemento anterior
	if ( (marcaAnterior != -1) && (ultimoClick != marcaAnterior) )
	{
		vecIconos[marcaAnterior] -> desMarcar();
		vecEventos[marcaAnterior] -> show();
	}
	//Marcamos el nuevo elemento
	if (ultimaMarca != -1)
	{
		vecIconos[ultimaMarca] -> marcar();
		vecEventos[ultimaMarca] -> show();
	}
	return true;
}

bool BarraIconos::clickear(GdkEventButton *E)
{
	int ultimoClick = Icono::getUltimoClick();
	int clickAnterior = Icono::getClickAnterior();

	//Desmarco el cuadro anteriormente clickeado
	if ( (ultimoClick != clickAnterior) && (clickAnterior != -2) )
	{
		vecIconos[clickAnterior] -> desMarcar();
		vecEventos[clickAnterior] -> show();
	}

	if (ultimoClick == clickAnterior) //Clickee mas de una vez en el mismo cuadro
	{
		vecIconos[ultimoClick] -> rotar();
		vecEventos[ultimoClick] -> show();
	}
	//Le aviso a la Tabla el numero de imagen y la rotacion
	if ( *T != NULL )
		(*T) -> setInfo(ultimoClick,vecIconos[ultimoClick] -> getRotacion());

	return true;
}

void  BarraIconos::activar()
{
	pCajaIconos -> set_sensitive(true);
}

void  BarraIconos::desActivar()
{
	pCajaIconos -> set_sensitive(false);
}
