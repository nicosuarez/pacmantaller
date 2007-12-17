#ifndef XML_PARSER_H_
#define XML_PARSER_H_

#include <libxml++/libxml++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "definiciones_editor.h"
#include "grafo.h"
#include "tabla.h"
#include "cordenada.h"

class XmlParser
{
	private:
		std::string obtenerOrientacion(int a,int cantFilas,int cantColumnas);
	public:
		int getProximoNivel();
		void armarArchivoNiveles(int nroNivel);
		void armarArchivoMapa(int nroNivel,int alto,int ancho,Grafo &G,std::list<RegElemento>& listaMod,std::list<Cordenada> listaVerticesCasa,std::string orientacion);
		void actualizarConfiguracion(int nroNivel);
		void armarArchivoEditorMapa(int nroNivel,int alto,int ancho,std::list<RegElemento>& listaEle,std::list<RegElemento>& listaMod);
		void parsearArchivoEditorMapa(int nroNivel,int &alto,int &ancho,std::list<RegElemento>& listaEle,std::list<RegElemento>& listaMod);
};

#endif /*XML_PARSER_H_*/
