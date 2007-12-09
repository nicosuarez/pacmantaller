/* Clase Grafo
* Descripcion:
* Clase que modela la red de conexion.
*/

#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <iostream>
#include <cstdlib>
#include "AppSettings.h"

template < class TipoIdVertice, class TipoDatoVertice, 
class TipoIdArco, class TipoDatoArco >
class Grafo{

public:
    typedef Vertice<TipoIdVertice,TipoDatoVertice,TipoIdArco, 
        TipoDatoArco> tVertice;
    typedef Arco<TipoIdVertice,TipoDatoVertice,TipoIdArco,TipoDatoArco>tArco;
    typedef typename std::list<tVertice*>::iterator tIterator;

private:
    std::list< tVertice* > listaVertices;
    tVertice* verticeFuente;
   
public:
    //Constructor       
    Grafo(){verticeFuente = NULL;}
    //Destructor
    ~Grafo()
    {
        tIterator it = listaVertices.begin();
        while(it != listaVertices.end())
        {
            delete (*it);
            it++;
        }
        listaVertices.clear();
    }
    /*----------------------------------------------------------------------------*/
    //Getter y Setter     
    tVertice* setFuente(TipoIdVertice id)
    {
        tVertice* vertice=getVertice(id);
        if(vertice!=NULL)
        {
            return this->verticeFuente = vertice;
        }
        return NULL;
    }
    /*----------------------------------------------------------------------------*/
    std::list<tVertice*>* getVertices()
    {
        return &listaVertices;
    }
    /*----------------------------------------------------------------------------*/
    //Metodos
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : retorna un puntero al vertice buscado. Si no lo encuentra 
    devuelve NULL.
    */
    tVertice* getVertice( TipoIdVertice id )/*const*/
    {
        tVertice verticeBuscado(id);
        tIterator it;
        for( it = listaVertices.begin() ; it != listaVertices.end(); it++ )
        {
            if( verticeBuscado ==  ( *(*it) ) ) 
                return *it;
        }
        return NULL;
    }
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : determina si el id asociado al vertice esta en el red o no.
    */
    bool existeVertice(TipoIdVertice id)
    {
        tVertice* verticeOrig = this->getVertice(id);
        return verticeOrig != NULL;
    }
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : agrega un vertice a la lista de vertices.
    */
    tVertice* agregarVertice(TipoIdVertice id,TipoDatoVertice *elemenVertice)
    {
        //obtengo el vertice origen si ya existe
        tVertice* vertice = this->getVertice(id);
        if( vertice == NULL )
        {
            tVertice *nuevoVertice = new tVertice( id, elemenVertice ) ;
            listaVertices.push_back( nuevoVertice );
            return nuevoVertice;
        }
        return vertice;
    }
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : agrega un arco a la lista de arcos del vertice origen.
    */
    tArco* agregarArco( tVertice *verticeOrigen, tVertice *verticeDestino, 
        TipoIdArco idArco, TipoDatoArco elemenArco )
    {
        tArco *nuevoArco=new tArco(idArco,elemenArco,verticeOrigen,
            verticeDestino);
        verticeOrigen->agregarArco( nuevoArco ); 
        return nuevoArco;
    }
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : determina si el red tiene o no vertices.
    */
    bool estaVacio()const
    {
        return listaVertices.empty();
    }
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : el arco queda eliminado del red.
    */
    void quitarArco(TipoIdArco id)
    {
        tArco *arcoBuscado;
        tIterator it;
        bool encontrado = false;
        for( it = listaVertices.begin(); it< listaVertices.end(); it++ )
        {
            arcoBuscado = (*it)->getArco(id);
            if( arcoBuscado != NULL )
            {
                *it->quitarArco( arcoBuscado );
                delete arcoBuscado;
                break;
            }
        }
    }
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : Elimina de la lista de vertices el vertice identificado por el 
    *      parametro id,y todos los arcos que lo referencian. 
    */
    void quitarVertice( TipoIdVertice id )
    {
        tVertice *vertice = getVertice( id );
        tArco *arco = NULL;
        tIterator it, itBorrar;
        //Primero elimino las aristas dirigidas al vertice a eliminar
        for( it = listaVertices.begin(); it != listaVertices.end(); it++ )
        {
            //Para cada vertice del red me fijo si si tiene algun arco
            //dirigido hacia el vertice a eliminar
            if( (*(*it)) == (*vertice) )
            {
                itBorrar = it;
                continue;
            }
            arco = (*it)->getArcoToVertice( *vertice );
            if( arco != NULL)
            {
                //Si encuentra una arista, la elimino
                (*it)->quitarArco(arco);
            }
            arco = NULL;
        }
        //se elimina el vertice
        delete(*itBorrar);
        listaVertices.erase( itBorrar );
    }

};

#endif
