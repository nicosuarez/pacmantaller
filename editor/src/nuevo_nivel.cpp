#include "nuevo_nivel.h"

NuevoNivel::NuevoNivel(Glib::RefPtr<Gnome::Glade::Xml> &refXmlAux):refXml(refXmlAux)
{
	refXml -> get_widget("VNuevo",pVNuevo);
	//Botones
	refXml -> get_widget("BAceptar",pBAceptar);
	refXml -> get_widget("BCancelar",pBCancelar);
	//Conexiones para los botones
	pBAceptar -> signal_clicked().connect( sigc::mem_fun(*this,&NuevoNivel::funcBAceptar) );
	pBCancelar -> signal_clicked().connect( sigc::mem_fun(*this,&NuevoNivel::funcBCancelar) );

	//Combos
	refXml -> get_widget("comboFilas",pComboFilas);
	refXml -> get_widget("comboColumnas",pComboColumnas);
	//Conexiones para los Combos
	pComboFilas -> get_entry() -> signal_changed().connect ( sigc::mem_fun(*this,&NuevoNivel::funcComboFilas) );
	pComboColumnas -> get_entry() -> signal_changed().connect ( sigc::mem_fun(*this,&NuevoNivel::funcComboColumnas) );
	//Llenamos los combos con los numeros de filas y columnas
	//Filas
	std::list<Glib::ustring> listaNumeros;
	for (int fila = 6 ; fila < MAX_CANT_FILAS ; fila += 1)
	{
		std::ostringstream caja;
		caja << fila;
		listaNumeros.push_back(caja.str());
	}
	pComboFilas -> set_popdown_strings(listaNumeros);
	//Columnas
	listaNumeros.clear();
	for (int columna = 6 ; columna < MAX_CANT_COLUMNAS ; columna += 1)
	{
		std::ostringstream caja;
		caja << columna;
		listaNumeros.push_back(caja.str());
	}
	pComboColumnas -> set_popdown_strings(listaNumeros);
}

void NuevoNivel::mostrar( void (*pFuncionAceptar)(int,int,void *pE) ,void *pE)
{
	pObjetoEditor = pE;
	NuevoNivel::pFuncionAceptar = pFuncionAceptar;
	pVNuevo -> show();
}

//Funcioes para los Botones
void NuevoNivel::funcBAceptar()
{
	pVNuevo -> hide();
	//Se le avisa a la ventana principal (el editor) que se preciono el boton "Aceptar"
	(*(pFuncionAceptar))(nroFila,nroColumna,pObjetoEditor);
}

void NuevoNivel::funcBCancelar()
{
	pVNuevo -> hide();
}

//Funciones para los Combos

void NuevoNivel::funcComboFilas()
{
	//Se toma el numero del combo y se grafa en la variable "nroFila"
	Gtk::Entry *pEntrada = pComboFilas -> get_entry();
	if (pEntrada)
	{
		std::istringstream caja( pEntrada -> get_text() );
		caja >> nroFila;

		std::cout << "Fila => El numero que queda es: " << nroFila << std::endl; //TODO
	
	}
}

void NuevoNivel::funcComboColumnas()
{
	//Se toma el numero del combo y se grafa en la variable "nroColumna"
	Gtk::Entry *pEntrada = pComboColumnas -> get_entry();
	if (pEntrada)
	{
		std::istringstream caja( pEntrada -> get_text() );
		caja >> nroColumna;

		std::cout << "Columna => El numero que queda es: " << nroColumna << std::endl; //TODO
	}
}
