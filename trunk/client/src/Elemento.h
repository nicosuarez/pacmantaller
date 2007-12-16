///////////////////////////////////////////////////////////
//  Elemento.h
//  Implementation of the Class Elemento
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_)
#define EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_


#include "Coordenada.h"
#include <GL/glut.h>


typedef enum tipoElemento
{
	tSalidaPacman, tCasaFantasmas, tPowerup, tBonus, tPastilla
};

typedef enum Orientacion
{
	Norte, Sur, Este, Oeste
};

typedef enum Estado
{
	Aparece, Desaparece 
};

/**
 * Clase que representa cualquier objeto que puede estar situado en el mapa
 */
class Elemento
{

public:
		
	Elemento( int posicion, Orientacion orientacion );
	
	Elemento( int posicion, Coordenada coord, Orientacion orientacion );
	
	virtual ~Elemento();

	int getPosicion();
	
	virtual tipoElemento getTipo()const = 0;
	
	Orientacion getOrientacion()const;
	
	Estado getEstado()const;

	Coordenada getCoordenada(); 

	
	void setOrientacion( Orientacion orientacion);
	
	void SetPosicion(int newVal);
	
	void setEstado( Estado estado );
	
	virtual void renderizar();
	
	virtual bool operator==( tipoElemento tipo) const = 0;
	
	void setCoordenada( Coordenada coord);

private:
	
	int posicion; //es el id del vertice donde se encuentra el elemento
	Orientacion orientacion;
	Estado estado;
	
protected:
	Coordenada coord;
	
};
#endif // !defined(EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_)