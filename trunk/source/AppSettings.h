/* AppSettings
* Descripcion:
* Definiciones generales de la aplicacion
*/ 

#ifndef __APP_SETTINGS_H__
#define __APP_SETTINGS_H__

#include "Elemento.h"
#include "Arco.h"
#include "Vertice.h"


template < class TipoIdVertice, class TipoDatoVertice, 
class TipoIdArco, class TipoDatoArco >
class Grafo;

typedef Grafo<int,Elemento,int,int> tGrafo;
typedef Vertice<int,Elemento,int,int> tVertice;
typedef Arco<int,Elemento,int,int> tArco;
typedef std::list<tArco*>::iterator tItArco;
typedef std::list<tArco*>::reverse_iterator tRevItArco;
typedef std::list<tVertice*>::iterator tItVertice;
typedef std::list<tVertice*> tListaVertice;
typedef std::list<tArco*> tListaArco;

#endif
