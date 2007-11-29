#include "tabla.h"
//Atributos estaticos de Tabla
std::map<Cordenada,Cuadro*> Tabla::mapCuadros;
int Tabla::nroImg = -1;
int Tabla::rot = -1;
int Tabla::cantFilas = 0;
int Tabla::cantColumnas = 0;
int Tabla::filaInicial = 0;
int Tabla::columnaInicial = 0;
void* Tabla::In = NULL;
TipoModo Tabla::modo = NADA;
std::list<RegElemento> Tabla::listaElementos;
std::list<RegElemento> Tabla::listaModificadores;

Tabla::Tabla(int parCantFilas,int parCantColumnas):Matriz(parCantFilas,parCantColumnas,true)
{
	cantFilas = parCantFilas;
	cantColumnas = parCantColumnas;
	for ( int fila = 0 ; fila < cantFilas ; fila += 1 )
		for ( int columna = 0 ; columna < cantColumnas ; columna += 1 )
		{
			Cuadro *A = new Cuadro(fila,columna);
			Cordenada C(fila,columna);
			mapCuadros[C] = A;
			//--------------TODO-----------------------------------------------------
			Gtk::EventBox *E = new Gtk::EventBox();
			E -> signal_button_press_event().connect( sigc::mem_fun(*A,&Cuadro::funcBoton) );
			E -> set_events(Gdk::ALL_EVENTS_MASK);
			E -> signal_enter_notify_event().connect( sigc::mem_fun(*A,&Cuadro::funcCursorEntra) );
			E -> signal_leave_notify_event().connect( sigc::mem_fun(*A,&Cuadro::funcCursorSale) );
			E -> set_visible_window(false);
			Matriz.attach(*E,columna,columna+1,fila,fila+1,Gtk::FILL,Gtk::FILL);
			//-------------TODO------------------------------------------------

			Matriz.attach(*A,columna,columna+1,fila,fila+1,Gtk::FILL,Gtk::FILL);
			A -> show();
		}
}

void Tabla::setModo(TipoModo parModo)
{
	static int nroImgAnt = -1,rotAnt = -1;

	if ( (modo == MODO_INSERTAR) && (parModo == MODO_ELIMINAR) )
	{
		//Como nroImg y rot tambien se usan y modifican en el modo Eliminar grafo los valores viejos para cuando
		//vuelva al insertar
		nroImgAnt = nroImg;
		rotAnt = rot;
	}
	if (parModo == MODO_INSERTAR)
	{
		nroImg = nroImgAnt;
		rot = rotAnt;
	}
	modo = parModo;
}

Gtk::Table& Tabla::getMatriz()
{
	//Retorna una referencia al Gtk:Table creado
	return(Matriz);
}

void Tabla::setInfo(int nroBoton,int rot)
{
	Tabla::rot = rot;
	nroImg = nroBoton;
}

void Tabla::crearImg()
{
	//Crea una instancia de Imag segun la rotacion y el numero de la imagen seleccionada
	if (nroImg == 0)
		In = (void*)new Imag0(mapCuadros,cantFilas,cantColumnas,rot);
	if (nroImg == 1)
		In = (void*)new Imag1(mapCuadros,cantFilas,cantColumnas,rot);
	if (nroImg == 2)
		In = (void*)new Imag2(mapCuadros,cantFilas,cantColumnas,rot);
	if (nroImg == 3)
		In = (void*)new Imag3(mapCuadros,cantFilas,cantColumnas,rot);
	if (nroImg == 4)
		In = (void*)new Imag4(mapCuadros,cantFilas,cantColumnas,rot);
	if (nroImg == 5)
		In = (void*)new Imag5(mapCuadros,cantFilas,cantColumnas,rot);
	if (nroImg == 6)
		In = (void*)new Imag6(mapCuadros,cantFilas,cantColumnas,rot);
	if (nroImg == 7)
		In = (void*)new Imag7(mapCuadros,cantFilas,cantColumnas,rot);
	if (nroImg == 8)
		In = (void*)new Imag8(mapCuadros,cantFilas,cantColumnas,rot);
}

void Tabla::marcar(int fila,int columna)
{
	std::cout<< "Marcar"<<std::endl;//TODO

	if ( (modo == MODO_INSERTAR) && (In == NULL) )
	{
		crearImg();
		if (nroImg != -1)
		{
			std::cout<< "Marcar: "<< rot << std::endl;//TODO
	 		((InsertarImag*)In) -> insertar(MARCAR,fila,columna);
		}
	}
	if ( (modo == MODO_ELIMINAR) && (In == NULL) )
	{
		Cordenada C(fila,columna);
		std::list<RegElemento>::iterator it = listaElementos.begin();
		std::list<Cordenada>::iterator itB;
		bool encontrado = false;
		std::list<Cordenada> lista;
		//Recorremos la lista de elementos en busca de la imagen y la rotacion a la cual pertenece el cuadrado
		while ( (!encontrado) && (it != listaElementos.end())  && (mapCuadros[C] -> ocupado()) )
		{	
			(*it).get(nroImg,rot,filaInicial,columnaInicial);

			crearImg();
			//Extraigo la lista de los vertices que componen la imagen y rotacion obtenida
			lista.clear();
			lista = ((InsertarImag*)In) -> getListaVertices(filaInicial,columnaInicial);
			//Busco el vertice seleccionado en la lista
			itB = find(lista.begin(),lista.end(),C);
			if (itB != lista.end() ) //El vertice seleccionado pertenece a esta imagen con esta rotacion
				encontrado = true;
			else
			{
				delete ((InsertarImag*)In);
				In = NULL;
			}
			it++;
		}
		if (encontrado) //Si el cuadro seleccionado pertence a una imagen saturo todos sus cuadros para que se note
		{
			while ( !lista.empty() )
			{
				mapCuadros [ lista.front() ] -> saturar();
				lista.pop_front();
			}
		}
	}
}

void Tabla::desMarcar(int fila,int columna)
{
	if (modo == MODO_INSERTAR)
	{
		if (In!=NULL) //No hice click
		{
			((InsertarImag*)In) -> insertar(LIMPIAR,fila,columna);
			delete ((InsertarImag*)In);
			In = NULL;
		}
	}
	if (modo == MODO_ELIMINAR)
	{
		if (In!=NULL) //No hice click y debo volver a la normalidad los cuadros que fueron saturados
		{
			std::cout<< "desMarcar"<<std::endl;//TODO
			std::list<Cordenada> lista = ((InsertarImag*)In) -> getListaVertices(filaInicial,columnaInicial);
			while (!lista.empty())
			{
				mapCuadros[lista.front()] -> normalizar();
				lista.pop_front();
			}
			delete ((InsertarImag*)In);
			In = NULL;
		}
	}
}

void Tabla::dibujar(int fila,int columna)
{
	//Toma el cuadro que esta en la cordenada(fila,columna) y dibuja la figura a partir del mismo
	std::cout << "Dibujando.." << std::endl; //TODO
	
	if (modo == MODO_INSERTAR)
	{
		if ( (In) != NULL )
		{
			if ( ((InsertarImag*)In) -> getPermiso() )
			{
				//El insertar ya valida que tenga permiso pero igual necesito saber si lo tengo para saber si se va a colocar un nuevo elemento o no
				((InsertarImag*)In) -> insertar(INSERTAR,fila,columna);
				//Grabo la informacion de la lista de elementos
				RegElemento R(nroImg,rot,fila,columna);
				if (nroImg < 6) //Elementos estructurales	
					listaElementos.push_back(R);
				else
					listaModificadores.push_back(R);
			}
			delete ((InsertarImag*)In);
			In = NULL;
		}
	}
	if (modo == MODO_ELIMINAR)
	{
		if ( (In) != NULL )
		{
			//Elimino la imagen marcada de la lista de Elementos
			RegElemento R(nroImg,rot,filaInicial,columnaInicial);
			std::list<RegElemento>:: iterator it = find (listaElementos.begin(),listaElementos.end(),R);
			if (it != listaElementos.end() ) //Deberia ocurrir
				listaElementos.erase(it);
			//Borro la imagen de la Tabla
			((InsertarImag*)In) -> darPermiso();//No necesito saber si el area a modificar es valida
			((InsertarImag*)In) -> insertar(LIMPIAR,filaInicial,columnaInicial);
			delete ((InsertarImag*)In);
			In = NULL;
		}
	}
}