#include "editor.h"

Editor::Editor(Glib::RefPtr<Gnome::Glade::Xml> &refXmlAux):refXml(refXmlAux),pVEditor(0),N(refXmlAux),B(refXmlAux),nroNivel(0),modo(MODO_INSERTAR)
{
}

void Editor::correr()
{
	refXml -> get_widget("VEditor",pVEditor);
	refXml -> get_widget("nuevo_nivel",pItemNuevo);
	refXml -> get_widget("cargar_nivel",pItemCargar);
	refXml -> get_widget("guardar_nivel",pItemGuardar);
	refXml -> get_widget("salir",pItemSalir);
	refXml -> get_widget("acerca_de",pItemAcerca);
	refXml -> get_widget("manual",pItemManual);
	refXml -> get_widget("cajaVertical",pCajaVertical);
	refXml -> get_widget("labelInfo",pLabelInfo);
	refXml -> get_widget("BotonAgregar",pBotonAgregar);
	refXml -> get_widget("BotonQuitar",pBotonQuitar);
	//Conexiones
	pItemNuevo -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemNuevo) );
	pItemCargar -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemCargar) );
	pItemGuardar -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemGuardar) );
	pItemSalir -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemSalir) );
	pItemManual -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemManual) );
	pItemAcerca -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemAcerca) );
	pBotonAgregar -> signal_clicked().connect(sigc::mem_fun(*this,&Editor::funcBotonAgregar) );
	pBotonQuitar -> signal_clicked().connect(sigc::mem_fun(*this,&Editor::funcBotonQuitar) );
	T = NULL;
	B.setearTabla(&T);
	B.desActivar();//Inicialmente no se debe seleccionar nada

	//Corremos la ventana
	Gtk::Main::run(*pVEditor);

	
}

//Funciones para los elemntos del menu

void Editor::funcItemNuevo()
{
	std::cout << "Presionè nuevo" << std::endl; //TODO

	N.mostrar(&funcAceptar,(void *)this);
}

void Editor::funcItemCargar()
{
	std::cout << "Presionè abrir" << std::endl;
}

void Editor::funcItemGuardar()
{
	std::cout << "Presionè guardar" << std::endl;
}

void Editor::funcItemSalir()
{
	std::cout << "Presionè Salir" << std::endl;
}

void Editor::funcItemAcerca()
{
	std::cout << "Presionè Acerca" << std::endl;
}

void Editor::funcItemManual()
{
	std::cout << "Presionè Manual" << std::endl;
}

//Funcion para cuando se preciona el borton "Aceptar" de la ventana de Nuevo Nivel
void Editor::funcAceptar(int nFila,int nColumna,void *pObjetoEditor)
{
	std::cout << "Se preciona Aceptar con: " << nFila << " ," << nColumna << std::endl;//TODO

	//Informo el nro del nivel
	std::ostringstream caja;
	std::string linea;
	caja << ((Editor*)pObjetoEditor) -> nroNivel;
	linea = "Numero de Nivel : ";
	linea += caja.str();
	( ((Editor*)pObjetoEditor) -> pLabelInfo ) -> set_text(linea);

	if ( ((Editor*)pObjetoEditor) -> T != NULL ) 
	{
		//Remuevo la tabla vieja y libero sus recursos
		Tabla *tAux = ((Editor*)pObjetoEditor) -> T;
		( ((Editor*)pObjetoEditor) -> pCajaVertical ) -> remove ( tAux -> getMatriz() );
		delete tAux;
	}
	//Creo la tabla
	((Editor*)pObjetoEditor) -> T = new Tabla(nFila,nColumna);
	//Adiero la tabla a VBox (cajaVertical del Editor
	Tabla *tAux = ((Editor*)pObjetoEditor) -> T;
	
	( ((Editor*)pObjetoEditor) -> pCajaVertical ) -> pack_start ( tAux -> getMatriz() );
	
	//Mostramos los elementos
	(tAux -> getMatriz()).show();
	( ((Editor*)pObjetoEditor) -> pCajaVertical ) -> show();
	((Editor*)pObjetoEditor) -> pVEditor -> show_all_children();

	//Le indicamos el modo a la tabla
	tAux -> setModo( ((Editor*)pObjetoEditor) -> modo);
	if ( ((Editor*)pObjetoEditor) -> modo == MODO_INSERTAR )
		( ((Editor*)pObjetoEditor) -> B ).activar();
}

//Funciones para los Botones de Insertar y Eliminar
void Editor::funcBotonAgregar()
{
	std::cout << "señal de insertar" << std::endl;//TODO 
	
	if (modo != MODO_INSERTAR) //Lo pregunto por que al apretar el quitar este tambien se llama
	{
		modo = MODO_INSERTAR;
		if ( T != NULL)
		{
			T -> setModo(modo);
			B.activar(); //La barra se activa para que se puedan seleccionar elementos
		}
	}
}

void Editor::funcBotonQuitar()
{
	std::cout << "señal de eliminar" << std::endl;//TODO
 	
	if (modo != MODO_ELIMINAR)
	{
		modo = MODO_ELIMINAR;
		if ( T != NULL)
		{
			T -> setModo(modo);
			B.desActivar(); //No debe ser posible seleccionar elementos
		
	}}
}
