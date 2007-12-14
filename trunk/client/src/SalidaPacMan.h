///////////////////////////////////////////////////////////
//  SalidaPacMan.h
//  Implementation of the Class SalidaPacMan
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_85575FEF_01A0_47d7_86AE_71ADBC8E965F__INCLUDED_)
#define EA_85575FEF_01A0_47d7_86AE_71ADBC8E965F__INCLUDED_

#include "Elemento.h"

/**
 * Clase que contiene la informacion de donde parte el pacman en el mapa
 * 
 */
class SalidaPacMan : public Elemento
{

public:
	
	SalidaPacMan( int posicion, Orientacion orientacion = Norte  );
	
	SalidaPacMan( int posicion, Coordenada coord, Orientacion orientacion = Norte  );
	
	virtual ~SalidaPacMan();
	
	tipoElemento getTipo()const;

	void renderizar();
	
	bool operator==( tipoElemento tipo) const;

};
#endif // !defined(EA_85575FEF_01A0_47d7_86AE_71ADBC8E965F__INCLUDED_)
