#include "ActualizarJuego.h"

ActualizarJuego::ActualizarJuego(pBool finalizoNivel)
{
	this->updateTime=100;
}

void ActualizarJuego::main()
{
	while(!seFinalizoElNivel())
	{
		
		//Armar mensaje status
	}
}

Mensaje* ActualizarJuego::armarMensajeStatus()
{
	//Chekear reglas del juego..
	
	//Termino el nivel?
	return NULL;
}

bool ActualizarJuego::chocaron()
{
	int punt=Modelo::getInstance()->GetPuntuacion();
	std::cout<<punt;
	return true;
}

bool ActualizarJuego::seFinalizoElNivel()
{
	return *finalizoNivel;
}
