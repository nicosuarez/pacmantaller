#ifndef ORIENTACION_H_
#define ORIENTACION_H_


typedef enum tipoOrientacion
{
	Norte, Sur, Este, Oeste
};

class Orientacion
{
	tipoOrientacion tOrientacion;
	
public:
	Orientacion( tipoOrientacion tOrientacion=Norte );
	
	virtual ~Orientacion();
	
	tipoOrientacion getTipo()const {return tOrientacion;};
	
	bool operator==( Orientacion otro )const;
};

#endif /*ORIENTACION_H_*/
