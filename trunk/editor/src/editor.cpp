#include "editor.h"

Editor::Editor(Glib::RefPtr<Gnome::Glade::Xml> &refXmlAux):refXml(refXmlAux),pVEditor(0),N(refXmlAux),A(refXmlAux),B(refXmlAux),nroNivel(0),modo(MODO_INSERTAR)
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
	refXml -> get_widget("cerrar_nivel",pItemCerrar);
	refXml -> get_widget("cajaVertical",pCajaVertical);
	refXml -> get_widget("labelInfo",pLabelInfo);
	refXml -> get_widget("BotonAgregar",pBotonAgregar);
	refXml -> get_widget("BotonQuitar",pBotonQuitar);
	refXml -> get_widget("dialogoGuardar",pDialogoGuardar);
	refXml -> get_widget("dialogoEditorError",pDialogoEditorError);
	refXml -> get_widget("labelEditorError",pLabelEditorError);
	//Conexiones
	pItemNuevo -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemNuevo) );
	pItemCargar -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemCargar) );
	pItemGuardar -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemGuardar) );
	pItemSalir -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemSalir) );
	pItemCerrar -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemCerrar) );
	pItemManual -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemManual) );
	pItemAcerca -> signal_activate().connect(sigc::mem_fun (*this,&Editor::funcItemAcerca) );
	pBotonAgregar -> signal_clicked().connect(sigc::mem_fun(*this,&Editor::funcBotonAgregar) );
	pBotonQuitar -> signal_clicked().connect(sigc::mem_fun(*this,&Editor::funcBotonQuitar) );
	T = NULL;
	B.setearTabla(&T);
	B.desActivar();//Inicialmente no se debe seleccionar nada
	pItemGuardar -> set_sensitive(false);//Inicialmente no se puede guardar nada
	pItemCerrar -> set_sensitive(false);//Inicialmente no se puede cerrar nada

	//Corremos la ventana
	Gtk::Main::run(*pVEditor);

	
}

//Funciones para los elemntos del menu

void Editor::funcItemNuevo()
{
	std::cout << "Presionè nuevo" << std::endl; //TODO
	int cantFilas,cantColumnas;
	
	N.correr();
	N.getDatos(cantFilas,cantColumnas);
	if (cantFilas != NINGUNO) //Se preciono aceptar
	{
		nroNivel = Parser.getProximoNivel();
		crearTabla(cantFilas,cantColumnas);
		//Ahora es posible guardar y cerrar
		pItemGuardar -> set_sensitive(true);
		pItemCerrar -> set_sensitive(true);
		pItemNuevo -> set_sensitive(false);//Ahora no se puede crear un nivel nuevo
		pItemCargar -> set_sensitive(false);//Ahora se puede cargar un nivel
	}
	
}

void Editor::funcItemCargar()
{
	std::cout << "Presionè abrir" << std::endl;//TODO
	int nroAux = Parser.getProximoNivel();
	if (nroAux-1 < 0) //No se creo ningun nivel anteriormente
	{
		pLabelEditorError -> set_text("No existe ningun nivel anteriormente creado");
		pDialogoEditorError -> run();
		pDialogoEditorError -> hide();
	}
	else
	{
		A.correr(nroAux-1);
		nroNivel = A.getNroSel();
		if (nroNivel != NINGUNO) //Se preciono Aceptar
		{
			//Aca va el abrir
			int alto = -1,ancho = -1;
			std::list<RegElemento> listaEle,listaMod;
			Parser.parsearArchivoEditorMapa(nroNivel,alto,ancho,listaEle,listaMod);
			crearTabla(alto,ancho);
			T -> setInfoAbrir(listaEle,listaMod);
			//Ahora es posible guardar y cerrar		
			pItemGuardar -> set_sensitive(true);
			pItemCerrar -> set_sensitive(true);
			pItemNuevo -> set_sensitive(false);//Ahora no se puede crear un nivel nuevo
			pItemCargar -> set_sensitive(false);//Ahora se puede cargar un nivel
		}
		std::cout << "El numero seleccionado para abrir fue: " << nroNivel << std::endl;//TODO
		 
	} 
}

void Editor::funcItemGuardar()
{
	std::cout << "Presionè guardar" << std::endl;//TODO
	//Primero compruebo que el grafo de la tabla sea valido
	std::string mensajeError;
	if ( T -> tablaValida(mensajeError) )
	{
		Parser.armarArchivoNiveles(nroNivel);
		int ancho,alto;
		T -> getTamanio(alto,ancho);
		std::string orientacion;
		std::list<Cordenada> listaVerticesCasa = T->getVerticesCasa(orientacion);
		Parser.armarArchivoMapa(nroNivel,alto,ancho,T->getGrafo(),T->getListaModificadores(),listaVerticesCasa,orientacion);
		Parser.armarArchivoEditorMapa(nroNivel,alto,ancho,T->getListaElementos(),T->getListaModificadores());
		Parser.actualizarConfiguracion(nroNivel);
		pDialogoGuardar -> run();
		pDialogoGuardar -> hide();
	}
	else
	{
		//Informo el error
		pLabelEditorError -> set_text(mensajeError.c_str());
		pDialogoEditorError -> run();
		pDialogoEditorError -> hide();
	}
}

void Editor::funcItemCerrar()
{
	std::cout << "Se preciono Cerrar" << std::endl; //TODO
	
	if ( T != NULL ) 
	{
		//Remuevo la tabla vieja y libero sus recursos
		pCajaVertical -> remove ( T -> getMatriz() );
		delete T;
		T = NULL;
		B.desActivar(); //La barra de elementos se desactiva
		pItemGuardar -> set_sensitive(false);
		pItemCerrar -> set_sensitive(false);//Ahora no hay mas nada que cerrar
		pItemNuevo -> set_sensitive(true);//Ahora se puede crear un nivel nuevo
		pItemCargar -> set_sensitive(true);//Ahora es posible abrir un nivrel
		pLabelInfo -> set_text("");
	}
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
void Editor::crearTabla(int nFila,int nColumna)
{
	std::cout << "Se preciona Aceptar con: " << nFila << " ," << nColumna << std::endl;//TODO

	//Informo el nro del nivel
	std::ostringstream caja;
	std::string linea;
	caja << nroNivel;
	linea = "Numero de Nivel : ";
	linea += caja.str();
	pLabelInfo -> set_text(linea);

	if ( T != NULL ) 
	{
		//Remuevo la tabla vieja y libero sus recursos
		 pCajaVertical -> remove ( T -> getMatriz() );
		delete T;
		T = NULL;
	}
	//Creo la tabla
	T = new Tabla(nFila,nColumna,refXml);
	//Adiero la tabla a VBox (cajaVertical del Editor
	pCajaVertical -> pack_start ( T -> getMatriz() );
	
	//Mostramos los elementos
	(T -> getMatriz()).show();
	pCajaVertical -> show();
	pVEditor -> show_all_children();

	//Le indicamos el modo a la tabla
	T-> setModo (modo);
	if ( modo == MODO_INSERTAR )
		B.activar();
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
		}
	}
}

Editor::~Editor()
{
	if ( T!= NULL)
		delete T;
}
