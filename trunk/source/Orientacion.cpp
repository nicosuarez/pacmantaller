#include "Orientacion.h"

Orientacion::Orientacion( tipoOrientacion tOrientacion ): tOrientacion(tOrientacion)
{
}

Orientacion::~Orientacion()
{
}

bool Orientacion::operator==( Orientacion otro )const
{
	return otro.getTipo() == this->getTipo();
}
