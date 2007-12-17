#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <string>
#include "AppSettings.h"
#include "StrToken.h"
#include "Modelo.h"
#include "Pastilla.h"
#include "PowerUp.h"
#include "Personaje.h"
#include "CasaFantasmas.h"
#include "Bonus.h"
#include <exception>
#include "LogResource.h"
#include "Mundo.h"
#include <vector>
#include <libxml++/parsers/textreader.h>

using std::string;

class XmlParser
{
private:
	static void setAncho(Mapa* mapa,xmlpp::TextReader& reader);
	static void setAlto(Mapa* mapa,xmlpp::TextReader& reader);
	static void cargarGrafo(Mapa* mapa,xmlpp::TextReader& reader);
	static int getAtributoInt(xmlpp::TextReader& reader,string atrib);
	static tVertice* agregarVertice(Mapa* mapa,int idVertice);
	static void cargarArista(Mapa* mapa,xmlpp::TextReader& reader,int arcoId,string orientacion);
	static void cargarPasillo(Mapa* mapa,int arcoId,string orientacion,int vIdOrig,int vIdDest);
	static void cargarMundo(Mundo* mundo,xmlpp::TextReader& reader);
	static Orientacion orientacionParser(string orientacion);
	static Orientacion getOrientacionContraria(string orientacion);
	static void agregarArista(Mapa* mapa,xmlpp::TextReader& reader);
	static void buscarElemento(xmlpp::TextReader& reader);
	static void mostrarNombre(xmlpp::TextReader& reader);
	static std::vector<int> elementosNoPastillas;
	
	//Agregar Elementos
	static bool agregarPastilla(int idVertice);
	static void agregarElementos(Mapa* mapa,xmlpp::TextReader& reader);
	static void agregarPowerUp(Mapa* mapa,xmlpp::TextReader& reader);
	static void agregarBonus(Mapa* mapa,xmlpp::TextReader& reader);
	static void agregarSalidaPacMan(Mapa* mapa,xmlpp::TextReader& reader);
	static void agregarCasaFantasmas(Mapa* mapa,xmlpp::TextReader& reader);
	static void agregarPastillas(Mapa* mapa);
public:
	XmlParser();
	static Mundo* getMundo(string mundoPath);
	static Mapa* getMapa(string mapaPath);

};

#endif /*XMLPARSER_H_*/
