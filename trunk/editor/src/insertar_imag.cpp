#include "insertar_imag.h"

//Clase InsertarImag
InsertarImag::InsertarImag(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot):mapCuadros(parMapCuadros),cantFilas(parCantFilas),cantColumnas(parCantColumnas),rot(parRot),permiso(false)
{
}

void InsertarImag::darPermiso()
{
	//Se usa para dibujar sabiendo que las pocisiones son validas
	permiso = true;
}

bool InsertarImag::getPermiso()
{
	return (permiso);
}

bool InsertarImag::valido(bool fila,int posInicial,int posFija,int cuanto)
{
	//Comprueba que se este dentro del rango de la tabla y que los cuadros que se van a ocupar esten vacios
	int valorMaximo;

	valorMaximo = (fila)? cantFilas:cantColumnas;
	if ( (posInicial + cuanto) > valorMaximo) //Esta fuera del rango de la tabla
	{
		std::cout << "Error!. Fuera de Rango" << std::endl; //TODO
		return false;
	}
	valorMaximo = (!fila)? cantFilas:cantColumnas;
	if ( (posFija >= valorMaximo) || (posFija < 0) )//Esta fuera del rango de la tabla
	{
		std::cout << "Error!. Fuera de Rango" << std::endl; //TODO
		return false;
	}
	for (int x = posInicial ; x <= (posInicial + cuanto - 1) ; x++)
	{
		Cordenada C;
		if (fila)
			C.set(x,posFija);
		else
			C.set(posFija,x);

		if ( mapCuadros[C] -> ocupado() ) //Ya hay un elemento en el cuadro
		{
			std::cout << "Error!. Cuadro Ocupado " << std::endl; //TODO
			return false;
		}
	}
	return true;
}

void InsertarImag::colocarImagen(Cordenada &C,TipoOperacion op,std::string &archivo)
{
	if ( op == MARCAR )	
		mapCuadros[C] -> setImagenMarca();
	if ( op == LIMPIAR )
		mapCuadros[C] -> setImagenBlanco();
	if ( op == INSERTAR )
		mapCuadros[C] -> setImagen(archivo);
}

int InsertarImag::insertarVertices(std::list<Cordenada> &listaCordenadas,std::list<Vertice*> &listaVertices,Grafo &G)
{
	int res = EXITO;
	std::list<Cordenada> listaAux;
	while ( (!listaVertices.empty()) && (res == EXITO) ) 
	{
		int f,c;
		(listaCordenadas.front()).get(f,c);
		res = G.agregarVertice(listaVertices.front(),f,c);
		if (res != ERROR)
		{
			listaAux.push_back( (listaCordenadas.front()) );
			listaVertices.pop_front();
		}
		listaCordenadas.pop_front();
	}
	if (res == ERROR)
	{
		//Elimino los vertices que puse
		while (!listaAux.empty())
		{
			int f,c;
			(listaAux.front()).get(f,c);
			G.eliminarVertice(f,c);
			listaAux.pop_front();
		}
		while(!listaVertices.empty())
		{
			delete listaVertices.front();
			listaVertices.pop_front();
		}
	}
	return res;
}
//Clases Derivadas

Imag0::Imag0(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot):InsertarImag(parMapCuadros,parCantFilas,parCantColumnas,parRot)
{}

void Imag0::insertar(TipoOperacion op,int fila,int columna)
{
	std::cout << "Estoy dibujando la 0" << std::endl; //TODO

	std::string archivo;

	if (rot == 0) //Lo dibujo en vertical
	{
		archivo = PATH_PUNTO_V;
		//Controlo que se este dentro del rango y que los cuadros no esten ocupados
		if ( op == MARCAR )
			permiso = valido(true,fila,columna,3);
		if (permiso)
			for (int f = fila ; f < fila +3 ; f++)
			{
				Cordenada C(f,columna);
				colocarImagen(C,op,archivo);
			}
	}
	else
	{
		//Otra Rotacion
		archivo = PATH_PUNTO_H;
		//Controlo que se este dentro del rango y que los cuadros no esten ocupados
		if ( op == MARCAR )
			permiso = valido(false,columna,fila,3);
		if (permiso)
			for (int c = columna ; c < columna +3 ; c++)
			{
				Cordenada C(fila,c);
				colocarImagen(C,op,archivo);
			}
	}
}

std::list<Cordenada> Imag0::getListaVertices(int fila,int columna)
{
	std::list<Cordenada> lista;
 
	for (int i = 0 ; i < 3 ; i++ )
	{
		if (rot == 0)
		{
			Cordenada C(fila+i,columna);
			lista.push_back(C);
		}
		else
		{
			Cordenada C(fila,columna+i);
			lista.push_back(C);
		}
	}
	return (lista); 
}

int  Imag0::actualizarGrafo(int fila,int columna,Grafo &G)
{
	int i = 0,res = EXITO;
	std::list<Cordenada> listaCordenadas;

	while ( (i < 3) && (res == EXITO) )
	{
		Vertice *V;
		if (rot == 0)
		{
			V = new Vertice(false,false,true,true,false);
			res = G.agregarVertice(V,fila+i,columna);
			if (res != ERROR)
			{
				Cordenada C(fila+i,columna);
				listaCordenadas.push_back(C);
			}
			else
				delete V;
		}
		else
		{
			V = new Vertice(true,true,false,false,false);
			res = G.agregarVertice(V,fila,columna+i);
			if (res != ERROR)
			{
				Cordenada C(fila,columna+i);
				listaCordenadas.push_back(C);
			}
			else
				delete V;
		}
		i++;
	}
	if (res == ERROR)
	{
		//Tengo que eliminar los vertices que puse
		while (!listaCordenadas.empty())
		{
			int f,c;
			Cordenada C = listaCordenadas.front();
			C.get(f,c);
			G.eliminarVertice(f,c);
			listaCordenadas.pop_front();
		}
	}
	
	return res;
}

//----------------------------------------------

Imag1::Imag1(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot):InsertarImag(parMapCuadros,parCantFilas,parCantColumnas,parRot)
{}

void Imag1::colocarParteVertical(TipoOperacion op,int fila,int columna)
{
	std::string archivo;
	//Coloca la parte vertical de la figura donde se lo indiquen
	for (int f = fila ; f < fila +1 ; f++)
	{
		Cordenada C(f,columna);
		archivo = (op == INSERTAR )? PATH_PUNTO_V:"";
		colocarImagen(C,op,archivo);
	}
}

void Imag1::colocarParteHorizontal(TipoOperacion op,int fila,int columna)
{
	std::string archivo;
	//Coloca la parte Horizontal donde lo indiquen
	for (int c = columna ; c < columna + 1 ; c++)
	{
		Cordenada C(fila,c);
		archivo = (op == INSERTAR )? PATH_PUNTO_H:"";
		colocarImagen(C,op,archivo);
	}
}

void Imag1::colocarConector(TipoOperacion op,int fila,int columna)
{
	std::string archivo;
	//Coloca el conector de la parte horizontal y vertical
	Cordenada C(fila,columna);
	if (op == INSERTAR )
	{
		if (rot == 0)
			archivo = PATH_PUNTO_C;
		if (rot == 1)
			archivo = PATH_PUNTO_CR1;
		if (rot == 2)
			archivo = PATH_PUNTO_CR2;
		if (rot == 3)
			archivo = PATH_PUNTO_CR3;
	}
	else
		archivo = "";

	colocarImagen(C,op,archivo);
}

void Imag1::insertarRot0(TipoOperacion op,int fila,int columna)
{
	std::string archivo;

	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
		if ( (permiso = valido(true,fila,columna,2)) )
			permiso = valido(false,columna,fila,2);
	if (permiso)
	{
		//Puntos Verticales
		colocarParteVertical(op,fila+1,columna);
		//Puntos Horizontales
		colocarParteHorizontal(op,fila,columna+1);
		//Conector
		colocarConector(op,fila,columna);
	}
}

void Imag1::insertarRot1(TipoOperacion op,int fila,int columna)
{
	std::string archivo;

	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
		if ( (permiso = valido(true,fila,columna+1,2)) )
			permiso = valido(false,columna,fila,2);
	if (permiso)
	{
		//Puntos Verticales
		colocarParteVertical(op,fila+1,columna+1);
		//Puntos Horizontales
		colocarParteHorizontal(op,fila,columna);
		//Conector
		colocarConector(op,fila,columna+1);
	}
}

void Imag1::insertarRot2(TipoOperacion op,int fila,int columna)
{
	std::string archivo;

	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
		if ( (permiso = valido(true,fila,columna+1,2)) )
			permiso = valido(false,columna,fila+1,2);
	if (permiso)
	{
		//Puntos Verticales
		colocarParteVertical(op,fila,columna+1);
		//Puntos Horizontales
		colocarParteHorizontal(op,fila+1,columna);
		//Conector
		colocarConector(op,fila+1,columna+1);
	}
}

void Imag1::insertarRot3(TipoOperacion op,int fila,int columna)
{
	std::string archivo;

	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
		if ( (permiso = valido(true,fila,columna,2)) )
			permiso = valido(false,columna,fila+1,2);
	if (permiso)
	{
		//Puntos Verticales
		colocarParteVertical(op,fila,columna);
		//Puntos Horizontales
		colocarParteHorizontal(op,fila+1,columna+1);
		//Conector
		colocarConector(op,fila+1,columna);
	}
}

void Imag1::insertar(TipoOperacion op,int fila,int columna)
{
	std::cout << "Estoy dibujando la 1" << std::endl; //TODO

	if (rot == 0) //Lo dibujo en vertical
		insertarRot0(op,fila,columna);
	if (rot == 1) //Lo dibujo en vertical
		insertarRot1(op,fila,columna);
	if (rot == 2) //Lo dibujo en vertical
		insertarRot2(op,fila,columna);
	if (rot == 3) //Lo dibujo en vertical
		insertarRot3(op,fila,columna);
}

std::list<Cordenada> Imag1::getListaVertices(int fila,int columna)
{
	std::list<Cordenada> lista;
	
	if ( (rot == 0) || (rot == 1) )
	{
		Cordenada C(fila,columna);
		lista.push_back(C);
		Cordenada C2(fila,columna+1);
		lista.push_back(C2);
		if (rot == 1)
			columna++;
		Cordenada C3(fila+1,columna);
		lista.push_back(C3);
	}
	if ( (rot == 2) || (rot == 3) )
	{
		Cordenada C(fila+1,columna);
		lista.push_back(C);
		Cordenada C2(fila+1,columna+1);
		lista.push_back(C2);
		if (rot == 2)
			columna++;
		Cordenada C3(fila,columna);
		lista.push_back(C3);
	}
	return(lista);
}

int  Imag1::actualizarGrafo(int fila,int columna,Grafo &G)
{
	std::list<Cordenada> listaCordenadas;
	std::list<Vertice*> listaVertices;

	
	if (rot == 0)
	{
		//1ero el Conector
		listaVertices.push_back (new Vertice(true,false,false,true) );
		listaCordenadas.push_back(Cordenada(fila,columna));
		listaVertices.push_back (new Vertice(true,true,false,false) );
		listaCordenadas.push_back(Cordenada(fila,columna+1));
		listaVertices.push_back (new Vertice(false,false,true,true) );
		listaCordenadas.push_back(Cordenada(fila+1,columna));
	}
	if (rot == 1)
	{
		//1ero el Conector
		listaVertices.push_back (new Vertice(false,true,false,true) );
		listaCordenadas.push_back(Cordenada(fila,columna+1));
		listaVertices.push_back (new Vertice(true,true,false,false) );
		listaCordenadas.push_back(Cordenada(fila,columna));
		listaVertices.push_back (new Vertice(false,false,true,true) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+1));
	}
	if (rot == 2)
	{
		//1ero el Conector
		listaVertices.push_back (new Vertice(false,true,true,false) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+1));
		listaVertices.push_back (new Vertice(false,false,true,true) );
		listaCordenadas.push_back(Cordenada(fila,columna+1));
		listaVertices.push_back (new Vertice(true,true,false,false) );
		listaCordenadas.push_back(Cordenada(fila+1,columna));
	}
	if (rot == 3)
	{
		//1ero el Conector
		listaVertices.push_back (new Vertice(true,false,true,false) );
		listaCordenadas.push_back(Cordenada(fila+1,columna));
		listaVertices.push_back (new Vertice(false,false,true,true) );
		listaCordenadas.push_back(Cordenada(fila,columna));
		listaVertices.push_back (new Vertice(true,true,false,false) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+1));
	}
	
	//Coloco los vertices
	return (insertarVertices(listaCordenadas,listaVertices,G));
}
//---------------

Imag2::Imag2(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot):InsertarImag(parMapCuadros,parCantFilas,parCantColumnas,parRot)
{}

void Imag2::colocarTramoVertical(TipoOperacion op,int fila,int columna,std::string medio)
{
	std::string archivo;
	for (int f = fila ; f < fila +3 ; f++)
	{
		if (f == fila+1)
			archivo = medio;
		else
			archivo = PATH_PUNTO_V;
		Cordenada C(f,columna);
		colocarImagen(C,op,archivo);
	}
}
void Imag2::colocarTramoHorizontal(TipoOperacion op,int fila,int columna,std::string medio)
{
	std::string archivo;
	for (int c = columna ; c < columna +3 ; c++)
	{
		if (c == columna+1)
			archivo = medio;
		else
			archivo = PATH_PUNTO_H;
		Cordenada C(fila,c);
		colocarImagen(C,op,archivo);
	}
}

void Imag2::colocarPunto(TipoOperacion op,int fila,int columna,std::string archivo)
{
	Cordenada C(fila,columna);
	colocarImagen(C,op,archivo);
}

void Imag2::insertarRot0(TipoOperacion op,int fila,int columna)
{
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
	if ( (permiso = valido(true,fila,columna,3)) )
		permiso = valido(true,fila+1,columna+1,1);
	if (permiso) 
	{	colocarTramoVertical(op,fila,columna,PATH_PUNTO_V2);
		colocarPunto(op,fila+1,columna+1,PATH_PUNTO_H);
	}
}

void Imag2::insertarRot1(TipoOperacion op,int fila,int columna)
{
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
	if ( (permiso = valido(false,columna,fila,3)) )
		permiso = valido(true,fila+1,columna+1,1);
	if (permiso) 
	{	colocarTramoHorizontal(op,fila,columna,PATH_PUNTO_H2);
		colocarPunto(op,fila+1,columna+1,PATH_PUNTO_V);
	}
}

void Imag2::insertarRot2(TipoOperacion op,int fila,int columna)
{
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
	if ( (permiso = valido(true,fila,columna+1,3)) )
		permiso = valido(false,columna,fila+1,1);
	if (permiso) 
	{	colocarTramoVertical(op,fila,columna+1,PATH_PUNTO_V2b);
		colocarPunto(op,fila+1,columna,PATH_PUNTO_H);
	}
}

void Imag2::insertarRot3(TipoOperacion op,int fila,int columna)
{
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
	if ( (permiso = valido(false,columna,fila+1,3)) )
		permiso = valido(true,fila,columna+1,1);
	if (permiso) 
	{	colocarTramoHorizontal(op,fila+1,columna,PATH_PUNTO_H2b);
		colocarPunto(op,fila,columna+1,PATH_PUNTO_V);
	}
}

void Imag2::insertar(TipoOperacion op,int fila,int columna)
{
	std::cout << "Estoy dibujando la 2" << std::endl; //TODO

	std::string archivo;
	if (rot == 0) //Lo dibujo en vertical
		insertarRot0(op,fila,columna);
	if (rot == 1) //Lo dibujo en vertical
		insertarRot1(op,fila,columna);
	if (rot == 2) //Lo dibujo en vertical
		insertarRot2(op,fila,columna);
	if (rot == 3) //Lo dibujo en vertical
		insertarRot3(op,fila,columna);
}

std::list<Cordenada> Imag2::getListaVertices(int fila,int columna)
{
	std::list<Cordenada> lista;

	if ( (rot == 0) || (rot == 2) )
	{
		if (rot == 0)
		{
			Cordenada C(fila+1,columna+1);
			lista.push_back(C);
		}
		else
		{
			Cordenada C(fila+1,columna);
			lista.push_back(C);
			columna++;
		}
		for (int i = 0; i < 3 ; i++)
		{
			Cordenada C(fila+i,columna);
			lista.push_back(C);
		}
	}
	if ( (rot == 1) || (rot == 3) )
	{
		if (rot == 1)
		{
			Cordenada C(fila+1,columna+1);
			lista.push_back(C);
		}
		else
		{
			Cordenada C(fila,columna+1);
			lista.push_back(C);
			fila++;
		}
		for (int i = 0; i < 3 ; i++)
		{
			Cordenada C(fila,columna+i);
			lista.push_back(C);
		}
	}
	return(lista);
}

int  Imag2::actualizarGrafo(int fila,int columna,Grafo &G)
{
	std::list<Cordenada> listaCordenadas;
	std::list<Vertice*> listaVertices;

	if ( (rot == 0) || (rot == 2) )
	{
		if (rot == 0)
		{
			listaVertices.push_back(new Vertice(true,false,true,true));
			listaCordenadas.push_back(Cordenada(fila+1,columna));
			listaVertices.push_back(new Vertice(true,true,false,false));
			listaCordenadas.push_back(Cordenada(fila+1,columna+1));
			
		}
		else
		{
			listaVertices.push_back(new Vertice(false,true,true,true));
			listaCordenadas.push_back(Cordenada(fila+1,columna+1));
			listaVertices.push_back(new Vertice(true,true,false,false));
			listaCordenadas.push_back(Cordenada(fila+1,columna));
			columna++;
		}
		for ( int i = 0 ; i < 4 ; i+=2 )
		{
			listaVertices.push_back(new Vertice(false,false,true,true));
			listaCordenadas.push_back(Cordenada(fila+i,columna));
		}
	}
	if ( (rot == 1) || (rot == 3) )
	{
		if (rot == 1)
		{
			listaVertices.push_back(new Vertice(true,true,false,true));
			listaCordenadas.push_back(Cordenada(fila,columna+1));
			listaVertices.push_back(new Vertice(false,false,true,true));
			listaCordenadas.push_back(Cordenada(fila+1,columna+1));
			
		}
		else
		{
			listaVertices.push_back(new Vertice(true,true,true,false));
			listaCordenadas.push_back(Cordenada(fila+1,columna+1));
			listaVertices.push_back(new Vertice(false,false,true,true));
			listaCordenadas.push_back(Cordenada(fila,columna+1));
			fila++;
		}
		for ( int i = 0 ; i < 4 ; i+=2 )
		{
			listaVertices.push_back(new Vertice(true,true,false,false));
			listaCordenadas.push_back(Cordenada(fila,columna+i));
		}
	}
	return (insertarVertices(listaCordenadas,listaVertices,G));
}
//---------------------------

Imag3::Imag3(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot):InsertarImag(parMapCuadros,parCantFilas,parCantColumnas,parRot)
{}

void Imag3::insertar(TipoOperacion op,int fila,int columna)
{
	std::cout << "Estoy dibujando la 3" << std::endl; //TODO

	std::string archivo;
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
		if ( (permiso = valido(true,fila,columna+1,3)) )
			permiso = valido(false,columna,fila+1,3);
	if (permiso)
	{
		//Puntos Verticales
		for (int f = fila ; f < fila +3 ; f+=2)
		{
			Cordenada C(f,columna+1);
			archivo = PATH_PUNTO_V;	
			colocarImagen(C,op,archivo);
		}
		//Puntos Horizontales
		for (int c = columna ; c < columna +3 ; c+=2)
		{
			Cordenada C(fila+1,c);
			archivo = PATH_PUNTO_H;
			colocarImagen(C,op,archivo);
		}
		//Conector del medio
		Cordenada C(fila+1,columna+1);
		archivo = PATH_PUNTO_N;
		colocarImagen(C,op,archivo);
	}
			
}

std::list<Cordenada> Imag3::getListaVertices(int fila,int columna)
{
	std::list<Cordenada> lista;

	for (int i = 0 ; i < 3 ; i+=1 )
	{
		Cordenada C(fila+i,columna+1);
		lista.push_back(C);
	}
	for (int i = 0 ; i < 3 ; i+=2 )
	{
		Cordenada C(fila+1,columna+i);
		lista.push_back(C);
	}
	return(lista);
}

int  Imag3::actualizarGrafo(int fila,int columna,Grafo &G)
{
	std::list<Cordenada> listaCordenadas;
	std::list<Vertice*> listaVertices;

	for (int i = 0 ; i < 3 ; i+=2 )
	{
		listaCordenadas.push_back( Cordenada(fila+i,columna+1) );
		listaVertices.push_back( new Vertice(false,false,true,true) );
	}
	//Medio
	listaCordenadas.push_back( Cordenada(fila+1,columna+1) );
	listaVertices.push_back( new Vertice(true,true,true,true) );
	for (int i = 0 ; i < 3 ; i+=2 )
	{
		listaCordenadas.push_back( Cordenada(fila+1,columna+i) );
		listaVertices.push_back( new Vertice(true,true,false,false) );
	}
	return (insertarVertices(listaCordenadas,listaVertices,G));
}
//--------------------------

Imag4::Imag4(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot):InsertarImag(parMapCuadros,parCantFilas,parCantColumnas,parRot)
{
}

void Imag4::insertarRot0(TipoOperacion op,int fila,int columna)
{
	std::string pathC1(PATH_PUNTO_C1),pathCL(PATH_PUNTO_CL),pathC2(PATH_PUNTO_C2),pathC4(PATH_PUNTO_C4);
	std::string pathC3(PATH_PUNTO_C3),pathCN(PATH_PUNTO_CN),pathC5(PATH_PUNTO_C5);
	
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
		if ( (permiso = valido(false,columna,fila,3)) )
			if ( permiso = valido(false,columna,fila+1,3) )
				permiso = valido(false,columna+1,fila+2,1);
	if (permiso)
	{
		int f = fila,c = columna;
		Cordenada C1(f,c),CL(f,c+1),C2(f,c+2),C4(f+1,c),CN(f+1,c+1),C3(f+1,c+2),C5(f+2,c+1);
		
		colocarImagen(C1,op,pathC1);
		colocarImagen(CL,op,pathCL);
		colocarImagen(C2,op,pathC2);
		colocarImagen(C3,op,pathC3);
		colocarImagen(C4,op,pathC4);
		colocarImagen(CN,op,pathCN);
		colocarImagen(C5,op,pathC5);
	}
}

void Imag4::insertarRot1(TipoOperacion op,int fila,int columna)
{
	std::string pathC1(PATH_PUNTO_C1),pathCIb(PATH_PUNTO_CIb),pathC2(PATH_PUNTO_C2),pathC4(PATH_PUNTO_C4);
	std::string pathC3(PATH_PUNTO_C3),pathCN(PATH_PUNTO_CN),pathC5b(PATH_PUNTO_C5b);
	
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
		if ( (permiso = valido(true,fila,columna+1,3)) )
			if ( permiso = valido(true,fila,columna+2,3) )
				permiso = valido(false,columna,fila+1,1);
	if (permiso)
	{
		int f = fila,c = columna;
		Cordenada C1(f,c+1),C2(f,c+2),C5b(f+1,c),CN(f+1,c+1),CIb(f+1,c+2),C4(f+2,c+1),C3(f+2,c+2);
		
		colocarImagen(C1,op,pathC1);
		colocarImagen(CIb,op,pathCIb);
		colocarImagen(C2,op,pathC2);
		colocarImagen(C3,op,pathC3);
		colocarImagen(C4,op,pathC4);
		colocarImagen(CN,op,pathCN);
		colocarImagen(C5b,op,pathC5b);
	}
}

void Imag4::insertarRot2(TipoOperacion op,int fila,int columna)
{
	std::string pathC1(PATH_PUNTO_C1),pathCIc(PATH_PUNTO_CIc),pathC2(PATH_PUNTO_C2),pathC4(PATH_PUNTO_C4);
	std::string pathC3(PATH_PUNTO_C3),pathCN(PATH_PUNTO_CN),pathC5c(PATH_PUNTO_C5c);
	
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
		if ( (permiso = valido(false,columna,fila+1,3)) )
			if ( permiso = valido(false,columna,fila+2,3) )
				permiso = valido(false,columna+1,fila,1);
	if (permiso)
	{
		int f = fila,c = columna;
		Cordenada C1(f+1,c),CN(f+1,c+1),C2(f+1,c+2),C4(f+2,c),CIc(f+2,c+1),C3(f+2,c+2),C5c(f,c+1);
		
		colocarImagen(C1,op,pathC1);
		colocarImagen(CIc,op,pathCIc);
		colocarImagen(C2,op,pathC2);
		colocarImagen(C3,op,pathC3);
		colocarImagen(C4,op,pathC4);
		colocarImagen(CN,op,pathCN);
		colocarImagen(C5c,op,pathC5c);
	}
}

void Imag4::insertarRot3(TipoOperacion op,int fila,int columna)
{
	std::string pathC1(PATH_PUNTO_C1),pathCId(PATH_PUNTO_CId),pathC2(PATH_PUNTO_C2),pathC4(PATH_PUNTO_C4);
	std::string pathC3(PATH_PUNTO_C3),pathCN(PATH_PUNTO_CN),pathC5d(PATH_PUNTO_C5d);
	
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
		if ( (permiso = valido(true,fila,columna,3)) )
			if ( permiso = valido(true,fila,columna+1,3) )
				permiso = valido(false,columna+2,fila+1,1);
	if (permiso)
	{
		int f = fila,c = columna;
		Cordenada C1(f,c),C2(f,c+1),CId(f+1,c),CN(f+1,c+1),C5d(f+1,c+2),C4(f+2,c),C3(f+2,c+1);
		
		colocarImagen(C1,op,pathC1);
		colocarImagen(CId,op,pathCId);
		colocarImagen(C2,op,pathC2);
		colocarImagen(C3,op,pathC3);
		colocarImagen(C4,op,pathC4);
		colocarImagen(CN,op,pathCN);
		colocarImagen(C5d,op,pathC5d);
	}
}

void Imag4::insertar(TipoOperacion op,int fila,int columna)
{
	std::cout << "Estoy dibujando la 4" << std::endl; //TODO
	
	if ( rot == 0 )
		insertarRot0(op,fila,columna);
	if ( rot == 1 )
		insertarRot1(op,fila,columna);
	if ( rot == 2 )
		insertarRot2(op,fila,columna);
	if ( rot == 3 )
		insertarRot3(op,fila,columna);
}

std::list<Cordenada> Imag4::getListaVertices(int fila,int columna)
{
	std::list<Cordenada> lista;
	
	if ( (rot == 0) || (rot == 2) )
	{
		if (rot == 0)
		{
			Cordenada C(fila+2,columna+1);
			lista.push_back(C);
		}
		else
		{
			Cordenada C(fila,columna+1);
			lista.push_back(C);
		}
		if (rot == 2)
			fila++;
		for(int f = 0; f < 2 ; f++)
			for(int c = 0; c < 3 ; c++)
			{
				Cordenada C(fila+f,columna+c);
				lista.push_back(C);
			}
	}
	if ( (rot == 1) || (rot == 3) )
	{
		if (rot == 1)
		{
			Cordenada C(fila+1,columna);
			lista.push_back(C);
		}
		else
		{
			Cordenada C(fila+1,columna+2);
			lista.push_back(C);
		}

		if (rot == 1)
			columna++;
		for(int c = 0; c < 2 ; c++)
			for(int f = 0; f < 3 ; f++)
			{
				Cordenada C(fila+f,columna+c);
				lista.push_back(C);
			}
	}
	return(lista);
}

int  Imag4::actualizarGrafo(int fila,int columna,Grafo &G)
{
	std::list<Cordenada> listaCordenadas;
	std::list<Vertice*> listaVertices;

	if (rot == 0)
	{
		listaVertices.push_back( new Vertice (true,false,false,true) );
		listaCordenadas.push_back(Cordenada(fila,columna));
		listaVertices.push_back( new Vertice (true,true,false,true) );
		listaCordenadas.push_back(Cordenada(fila,columna+1));
		listaVertices.push_back( new Vertice (false,true,false,true) );
		listaCordenadas.push_back(Cordenada(fila,columna+2));
		listaVertices.push_back( new Vertice (true,false,true,false) );
		listaCordenadas.push_back(Cordenada(fila+1,columna));
		listaVertices.push_back( new Vertice (true,true,true,true) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+1));
		listaVertices.push_back( new Vertice (false,true,true,false) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+2));
		//Conector
		listaVertices.push_back( new Vertice (false,false,true,true) );
		listaCordenadas.push_back(Cordenada(fila+2,columna+1));
	}
	if (rot == 1)
	{
		listaVertices.push_back( new Vertice (true,false,false,true) );
		listaCordenadas.push_back(Cordenada(fila,columna+1));
		listaVertices.push_back( new Vertice (false,true,false,true) );
		listaCordenadas.push_back(Cordenada(fila,columna+2));
		listaVertices.push_back( new Vertice (true,true,true,true) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+1));
		listaVertices.push_back( new Vertice (false,true,true,true) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+2));
		listaVertices.push_back( new Vertice (true,false,true,false) );
		listaCordenadas.push_back(Cordenada(fila+2,columna+1));
		listaVertices.push_back( new Vertice (false,true,true,false) );
		listaCordenadas.push_back(Cordenada(fila+2,columna+2));
		//Conector
		listaVertices.push_back( new Vertice (true,true,false,false) );
		listaCordenadas.push_back(Cordenada(fila+1,columna));
	}
	if (rot == 2)
	{
		listaVertices.push_back( new Vertice (true,false,false,true) );
		listaCordenadas.push_back(Cordenada(fila+1,columna));
		listaVertices.push_back( new Vertice (true,true,true,true) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+1));
		listaVertices.push_back( new Vertice (false,true,false,true) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+2));
		listaVertices.push_back( new Vertice (true,false,true,false) );
		listaCordenadas.push_back(Cordenada(fila+2,columna));
		listaVertices.push_back( new Vertice (true,true,true,false) );
		listaCordenadas.push_back(Cordenada(fila+2,columna+1));
		listaVertices.push_back( new Vertice (false,true,true,false) );
		listaCordenadas.push_back(Cordenada(fila+2,columna+2));
		//Conector
		listaVertices.push_back( new Vertice (false,false,true,true) );
		listaCordenadas.push_back(Cordenada(fila,columna+1));
	}
	if (rot == 3)
	{
		listaVertices.push_back( new Vertice (true,false,false,true) );
		listaCordenadas.push_back(Cordenada(fila,columna));
		listaVertices.push_back( new Vertice (false,true,false,true) );
		listaCordenadas.push_back(Cordenada(fila,columna+1));
		listaVertices.push_back( new Vertice (true,false,true,true) );
		listaCordenadas.push_back(Cordenada(fila+1,columna));
		listaVertices.push_back( new Vertice (true,true,true,true) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+1));
		listaVertices.push_back( new Vertice (true,false,true,false) );
		listaCordenadas.push_back(Cordenada(fila+2,columna));
		listaVertices.push_back( new Vertice (false,true,true,false) );
		listaCordenadas.push_back(Cordenada(fila+2,columna+1));
		//Conector
		listaVertices.push_back( new Vertice (true,true,false,false) );
		listaCordenadas.push_back(Cordenada(fila+1,columna+2));
	}
	return (insertarVertices(listaCordenadas,listaVertices,G));
}
//--------------------------
Imag5::Imag5(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot):InsertarImag(parMapCuadros,parCantFilas,parCantColumnas,parRot)
{}

void Imag5::colocarTramoVertical(TipoOperacion op,int fila,int columna)
{
	std::string archivo;
	for (int f = fila ; f < fila +3 ; f+=2)
	{
		Cordenada C(f,columna);
		archivo = PATH_PUNTO_V;
		colocarImagen(C,op,archivo);
	}
}

void Imag5::colocarTramoHorizontal(TipoOperacion op,int fila,int columna)
{
	std::string archivo;
	for ( int c = columna ; c < columna + 3 ; c+=2 )
	{
		Cordenada C(fila,c);
		archivo = PATH_PUNTO_H;
		colocarImagen(C,op,archivo);
	}
}

void Imag5::colocarPasaje(TipoOperacion op,int fila,int columna,std::string archivo)
{
	Cordenada C(fila,columna);
	colocarImagen(C,op,archivo);
}

void Imag5::insertarRot0y2(TipoOperacion op,int fila,int columna)
{
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
	{
		permiso = ( (rot == 0) && (columna == cantColumnas-1) && (valido(true,fila,columna,3)) && (valido(true,fila,0,3)));
		if (!permiso)
			permiso = ( (rot == 2) && (columna == 0) && (valido(true,fila,columna,3)) && (valido(true,fila,cantColumnas-1,3)) );
	}
	if (permiso)
	{
		//Coloco la parte izquierda
		colocarTramoVertical(op,fila,0);
		colocarPasaje(op,fila+1,0,PATH_PUNTO_F2);
		//Coloco la parte de la derecha
		colocarTramoVertical(op,fila,cantColumnas-1);
		colocarPasaje(op,fila+1,cantColumnas-1,PATH_PUNTO_F);
		
	}
}

void Imag5::insertarRot1y3(TipoOperacion op,int fila,int columna)
{
	//Controlo que se este dentro del rango y que los cuadros no esten ocupados
	if ( op == MARCAR )
	{
		permiso = ( (rot == 1) && (fila == cantFilas-1) && (valido(false,columna,fila,3)) && (valido(false,columna,0,3)) );
		if (!permiso)
			permiso = ( (rot == 3) && (fila == 0) && (valido(false,columna,fila,3)) && (valido(false,columna,cantFilas-1,3)) );
	}
	if (permiso)
	{
		//Coloco la parte de arriba
		colocarTramoHorizontal(op,0,columna);
		colocarPasaje(op,0,columna+1,PATH_PUNTO_F3);
		//Coloco la parte de abajo
		colocarTramoHorizontal(op,cantFilas-1,columna);
		colocarPasaje(op,cantFilas-1,columna+1,PATH_PUNTO_F4);
		
	}
}

void Imag5::insertar(TipoOperacion op,int fila,int columna)
{
	std::cout << "Estoy dibujando la 5" << std::endl; //TODO

	std::string archivo;
	if ( (rot == 0) || (rot == 2) ) //Lo dibujo en vertical
		insertarRot0y2(op,fila,columna);
	if ( (rot == 1) || (rot == 3) ) //Lo dibujo en horizontal
		insertarRot1y3(op,fila,columna);
}

std::list<Cordenada> Imag5::getListaVertices(int fila,int columna)
{
	std::list<Cordenada> lista;
 
	for (int i = 0 ; i < 3 ; i++ )
	{
		if ( (rot == 0) || (rot == 2) )
		{
			Cordenada C(fila+i,cantColumnas-1);
			lista.push_back(C);
			Cordenada C2(fila+i,0);
			lista.push_back(C2);
		}
		else
		{
			Cordenada C(0,columna+i);
			lista.push_back(C);
			Cordenada C2(cantFilas-1,columna+i);
			lista.push_back(C2);
		}
	}
	return (lista); 
}

int  Imag5::actualizarGrafo(int fila,int columna,Grafo &G)
{
	std::list<Cordenada> listaCordenadas;
	std::list<Vertice*> listaVertices;

	if ( (rot == 0) || (rot == 2) )
	{
		for (int i = 0; i < 3 ; i+=2)
		{
			listaVertices.push_back( new Vertice (false,false,true,true) );
			listaCordenadas.push_back(Cordenada(fila+i,0));
			listaVertices.push_back( new Vertice (false,false,true,true) );
			listaCordenadas.push_back(Cordenada(fila+i,cantColumnas-1));
		}
		//Portales
		listaVertices.push_back( new Vertice (false,true,true,true,true) );
		listaCordenadas.push_back(Cordenada(fila+1,0));
		listaVertices.push_back( new Vertice (true,false,true,true,true) );
		listaCordenadas.push_back(Cordenada(fila+1,cantColumnas-1));
	}
	if ( (rot == 1) || (rot == 3) )
	{
		for (int i = 0; i < 3 ; i+=2)
		{
			listaVertices.push_back( new Vertice (true,true,false,false) );
			listaCordenadas.push_back(Cordenada(0,columna+i));
			listaVertices.push_back( new Vertice (true,true,false,false) );
			listaCordenadas.push_back(Cordenada(cantFilas-1,columna+i));
		}
		//Portales
		listaVertices.push_back( new Vertice (true,true,true,false,true) );
		listaCordenadas.push_back(Cordenada(0,columna+1));
		listaVertices.push_back( new Vertice (true,true,false,true,true) );
		listaCordenadas.push_back(Cordenada(cantFilas-1,columna+1));
	}
	return (insertarVertices(listaCordenadas,listaVertices,G));
}
//----------------------------

Imag6::Imag6(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot):InsertarImag(parMapCuadros,parCantFilas,parCantColumnas,parRot)
{}

void Imag6::insertar(TipoOperacion op,int fila,int columna)
{
	std::cout << "Estoy dibujando la 6" << std::endl; //TODO
	std::string archivo;
	Cordenada C(fila,columna);

	permiso = (mapCuadros[C] -> ocupado());
	if ( permiso  && (op == INSERTAR) )
		if (rot == 0) //Lo dibujo en vertical
		{
			//Controlo que se este dentro del rango y que los cuadros no esten ocupados
			archivo = PATH_PUNTO_P;
			colocarImagen(C,op,archivo);
		}
}

std::list<Cordenada> Imag6::getListaVertices(int fila,int columna)
{
	std::list<Cordenada> lista;
	Cordenada C(fila,columna);
	lista.push_back(C);
	return (lista);
}

//-----------------------------

Imag7::Imag7(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot):InsertarImag(parMapCuadros,parCantFilas,parCantColumnas,parRot)
{}

void Imag7::insertar(TipoOperacion op,int fila,int columna)
{
	std::cout << "Estoy dibujando la 7" << std::endl; //TODO
	std::string archivo;
	Cordenada C(fila,columna);

	permiso = (mapCuadros[C] -> ocupado());
	if ( permiso && (op == INSERTAR) )
		if (rot == 0) //Lo dibujo en vertical
		{
			//Controlo que se este dentro del rango y que los cuadros no esten ocupados
			archivo = PATH_PUNTO_POW;
			colocarImagen(C,op,archivo);
		}
}

std::list<Cordenada> Imag7::getListaVertices(int fila,int columna)
{
	std::list<Cordenada> lista;
	Cordenada C(fila,columna);
	lista.push_back(C);
	return (lista);
}

//---------------------------------

Imag8::Imag8(std::map<Cordenada,Cuadro*> &parMapCuadros,int parCantFilas,int parCantColumnas,int parRot):InsertarImag(parMapCuadros,parCantFilas,parCantColumnas,parRot)
{}

void Imag8::insertar(TipoOperacion op,int fila,int columna)
{
	std::cout << "Estoy dibujando la 8" << std::endl; //TODO
	std::string archivo;
	Cordenada C(fila,columna);

	permiso = (mapCuadros[C] -> ocupado());
	if ( permiso && (op == INSERTAR) )
		if (rot == 0) //Lo dibujo en vertical
		{
			//Controlo que se este dentro del rango y que los cuadros no esten ocupados
			archivo = PATH_PUNTO_BONUS;
			colocarImagen(C,op,archivo);
		}
}

std::list<Cordenada> Imag8::getListaVertices(int fila,int columna)
{
	std::list<Cordenada> lista;
	Cordenada C(fila,columna);
	lista.push_back(C);
	return (lista);
}
