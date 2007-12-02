#include "CerrarServidorOp.h"

CerrarServidorOp::CerrarServidorOp()
{
}

bool CerrarServidorOp::ejecutar(Modelo* modelo)
{
	std::cout<< "SE CERRO EL SERVIDOR...\n";
	//Crear mensaje stop
	
	//Enviar mensaje stop a todos los jugadores
	std::cout<<"Enviar mensaje STOP\n";
	
	//Finalizar el juego.
	modelo->seFinalizoElJuego(true);
	modelo->seFinalizoElNivel(true);
	
	return false;
}

