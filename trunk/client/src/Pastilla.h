///////////////////////////////////////////////////////////
//  Pastilla.h
//  Implementation of the Class Pastilla
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_E5344A0D_5B2C_472e_A1CA_57D31E44805B__INCLUDED_)
#define EA_E5344A0D_5B2C_472e_A1CA_57D31E44805B__INCLUDED_

#include "Elemento.h"

/**
 * Clase que representa una pastilla en el mapa
 */
class Pastilla : public Elemento
{

public:
	Pastilla( int posicion, Orientacion orientacion );
	
	virtual ~Pastilla();
	
	tipoElemento getTipo()const;

	virtual void renderizar();

};
#endif // !defined(EA_E5344A0D_5B2C_472e_A1CA_57D31E44805B__INCLUDED_)
