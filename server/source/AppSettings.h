/* AppSettings
* Descripcion:
* Definiciones generales de la aplicacion
*/ 

#ifndef __APP_SETTINGS_H__
#define __APP_SETTINGS_H__

#ifdef __GNUC__
#define PACKED __attribute__((__packed__))
#else
#error Debe compilar con GCC
#endif

#include "Elemento.h"
#include "Arco.h"
#include "Vertice.h"
#include "Grafo.h"
#include "Orientacion.h"

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


typedef struct PktElemento
{
	uint8_t tipo: 6;
	uint8_t orientacion: 2;
	uint16_t posicion;
}__attribute__((__packed__));

typedef struct PktPosiciones
{
	uint16_t id;
	uint32_t arista: 17;
	uint8_t posicion: 6;
	uint8_t direccion: 1;
}__attribute__((__packed__));

#endif
