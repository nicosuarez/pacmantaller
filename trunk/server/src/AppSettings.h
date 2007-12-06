/* AppSettings
* Descripcion:
* Definiciones generales de la aplicacion
*/ 

#ifndef __APP_SETTINGS_H__
#define __APP_SETTINGS_H__

#include "Elemento.h"
#include "Arco.h"
#include "Vertice.h"
#include "Grafo.h"

template < class TipoIdVertice, class TipoDatoVertice, 
class TipoIdArco, class TipoDatoArco >
class Grafo;

typedef Grafo<int,Elemento,int,Orientacion> tGrafo;
typedef Vertice<int,Elemento,int,Orientacion> tVertice;
typedef Arco<int,Elemento,int,Orientacion> tArco;
typedef std::list<tArco*>::iterator tItArco;
typedef std::list<tArco*>::reverse_iterator tRevItArco;
typedef std::list<tVertice*>::iterator tItVertice;
typedef std::list<tVertice*> tListaVertice;
typedef std::list<tArco*> tListaArco;
typedef std::list<Elemento*> tListaElemento;

#endif
