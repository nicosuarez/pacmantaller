/* Clase Vertice
* Descripcion:
* Clase que modela un nodo en el red.
*/

#ifndef __VERTICE_H__
#define __VERTICE_H__
#include <list>
#include <iostream>

template <class TipoIdVertice,class TipoDatoVertice,class TipoIdArco, 
class TipoDatoArco> class Arco;


template <class TipoIdVertice,class TipoDatoVertice,class TipoIdArco,
class TipoDatoArco>
class Vertice{

public:
    typedef Arco<TipoIdVertice,TipoDatoVertice,TipoIdArco,TipoDatoArco>tArco;
    typedef typename std::list<tArco*>::iterator tIterator;

private:
    std:: list< tArco* > listaArcos;
    TipoIdVertice idVertice;
    TipoDatoVertice *elemento;

public:
    //Contructor y Destructor       
    Vertice( TipoIdVertice id, TipoDatoVertice *elemento )
    {
        this->elemento = elemento;
        this->idVertice = id;
    }

    Vertice( TipoIdVertice id )
    {
        this->elemento = NULL;
        this->idVertice = id;
    }

    ~Vertice()
    {
        tIterator it;
        for( it=listaArcos.begin(); it != listaArcos.end(); it++ )
        {     
            delete *it;  
        }
        delete(elemento);
        listaArcos.clear();
    }
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : agrega un arco a la lista de arcos del vertice.
    */
    void agregarArco( tArco *arco )
    {
        listaArcos.push_front( arco );
    }

    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : Elimina el arco de la lista de arcos.
    */
    void quitarArco( tArco *arco )
    {
        tIterator it;
        for( it= listaArcos.begin(); it != listaArcos.end(); it++ )
            if( (*(*it)) == (*arco) )
            {
                delete (*it);
                listaArcos.erase( it );
                break;
            }
    }
    /*----------------------------------------------------------------------------*/
    //Setter y Getters
    void setElemento(TipoDatoVertice *elemento){this->elemento = elemento;}

    TipoDatoVertice* getElemento()const{return elemento;}

    void setid(TipoIdVertice *id){this->idVertice = id;}

    TipoIdVertice getid()const{return idVertice;}

    std:: list<tArco*>* getArcos(){return &listaArcos;}
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : Busca el arco que tenga el id pasado por parametro. Si lo 
    encuentra retorna un puntero al arco, sino retorna NULL.
    */
    tArco* getArco( TipoIdArco id )
    {
        tArco arco(id);
        tIterator it;
        for( it = listaArcos.begin(); it != listaArcos.end(); it++ )
            if( arco == (*(*it)) )
                return *it;
        return NULL;
    }
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : retorna un puntero al arco que tiene como vertice destino 
    el vertice pasado como parametro.
    */
    tArco* getArcoToVertice(Vertice &vertice)
    {
        if( listaArcos.empty() )
            return NULL;
        tIterator it;
        for( it = listaArcos.begin(); it!= listaArcos.end(); it++ )
        {
            Vertice *verticeDestino = (*it)->getVerticeDestino();
            if( (*verticeDestino) == vertice )
                return (*it);
        }
        return NULL;
    }
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : Compara los id del los vertices
    */
    bool operator==(const Vertice &vertice) const
    {
        return ( this->idVertice == vertice.idVertice );
    }
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : muesta por stdout la lista de arcos del vertice.
    */
    void imprimirArcos()
    {
        tIterator it = listaArcos.begin();
        for( it; it != listaArcos.end(); it++ )
            std::cout << (*it)->getid() << " ";
        std::cout << std::endl;
    }

};

#endif
