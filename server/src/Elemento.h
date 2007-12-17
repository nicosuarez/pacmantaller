///////////////////////////////////////////////////////////
//  Elemento.h
//  Implementation of the Class Elemento
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_)
#define EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_

typedef enum tipoElemento
{
	tSalidaPacman=0, tCasaFantasmas=1, tPowerup=2, tBonus=3, tPastilla=4
};

typedef enum Orientacion
{
	Norte=0, Este=1, Sur=2, Oeste=3
};

typedef enum Estado
{
	Desaparece=0,Aparece=1,Inicial=2,FueComido=3,Eliminado=4
};

/**
 * Clase que representa cualquier objeto que puede estar situado en el mapa
 */
class Elemento
{

public:
		
	Elemento( int posicion, Orientacion orientacion );
	
	virtual ~Elemento();

	int getPosicion();
	
	virtual tipoElemento getTipo()const = 0;
	
	virtual int getPuntaje(){return 0;};
	
	Orientacion getOrientacion()const;
	
	Estado getEstado()const;
	
	void setOrientacion( Orientacion orientacion);
	
	void SetPosicion(int posicion);
	
	void setEstado( Estado estado );
	
	virtual void renderizar();
	
	virtual bool operator==( tipoElemento tipo) const = 0;

private:
	
	int posicion; //es el id del vertice donde se encuentra el elemento
	Orientacion orientacion;
	Estado estado;
};
#endif // !defined(EA_F887A8C4_26A7_4b56_9859_BC974BB6BA04__INCLUDED_)
