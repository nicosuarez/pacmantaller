/* Clase Arco
* Descripcion:
* Clase que modela una arista del red
*/

#ifndef __ARCO_H__
#define __ARCO_H__

#include <iostream>

template <class TipoIdVertice, class TipoDatoVertice,
class TipoIdArco, class TipoDatoArco > class Vertice;

template <class TipoIdVertice,class TipoDatoVertice,class TipoIdArco,
class TipoDatoArco>
class Arco{

public:
    typedef Vertice<TipoIdVertice, TipoDatoVertice, TipoIdArco, 
        TipoDatoArco> tVertice;

private:
    tVertice *vOrigen, *vDestino;
    TipoIdArco idArco;
    TipoDatoArco *elemento;

public:
    //Contructores y Destructores

    Arco(TipoIdArco id)
    {
        this->idArco = id;
        this->elemento = NULL;
    }

    Arco(TipoIdArco id,TipoDatoArco *elemento)
    {
        this->idArco = id;
        this->elemento = elemento;
    }

    Arco(TipoIdArco id,TipoDatoArco *elemento,tVertice *vOrigen, 
        tVertice *vDestino)
    {
        this->idArco = id;
        this->elemento = elemento;
        this->vOrigen = vOrigen;
        this->vDestino = vDestino;
    }        

    ~Arco()
    {
        delete(elemento);
    }
    /*----------------------------------------------------------------------------*/
    //Getters y Setters
    /*----------------------------------------------------------------------------*/
    void setid( TipoIdArco id){this->idArco = id;}
    /*----------------------------------------------------------------------------*/
    TipoIdArco getid()const{return idArco;}
    /*----------------------------------------------------------------------------*/
    void setElemento( TipoDatoArco *elemento ){this->elemento = elemento;}
    /*----------------------------------------------------------------------------*/
    /*Devuelve el elemento contenido*/
    TipoDatoArco* getElemento(){return elemento;}
    /*----------------------------------------------------------------------------*/
    void setVerticeOrigen(tVertice *vOrigen){this->vOrigen= vOrigen;}
    /*----------------------------------------------------------------------------*/
    void setVerticeDestino(tVertice *vDestino){this->vDestino = vDestino;}
    /*----------------------------------------------------------------------------*/
    tVertice* getVerticeOrigen(){return vOrigen;}
    /*----------------------------------------------------------------------------*/
    tVertice* getVerticeDestino(){return vDestino;}
    /*----------------------------------------------------------------------------*/
    /*
    pre : ninguna
    post : Compara los id del los arcos
    */
    bool operator==(const Arco &arco) const
    {
        return ( this->idArco == arco.idArco );
    }
    /*----------------------------------------------------------------------------*/       

};

#endif
