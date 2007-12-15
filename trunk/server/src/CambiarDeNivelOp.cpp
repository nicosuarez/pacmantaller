#include "CambiarDeNivelOp.h"

CambiarDeNivelOp::CambiarDeNivelOp()
{
}

CambiarDeNivelOp::~CambiarDeNivelOp()
{
}

bool CambiarDeNivelOp::ejecutar()
{
	Modelo* modelo = Modelo::getInstance();
	modelo->seFinalizoElNivel(true);
	modelo->liberarNivel();
	return true;
}
