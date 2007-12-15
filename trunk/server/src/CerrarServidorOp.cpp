#include "CerrarServidorOp.h"

CerrarServidorOp::CerrarServidorOp()
{
}

bool CerrarServidorOp::ejecutar()
{
	//Enviar mensaje Quit a todos los jugadores
	std::cout<<"Enviar mensaje QUIT\n";
	Quit *quit = new Quit;
	Modelo *modelo = Modelo::getInstance();
	
	//Finalizar el juego.
	modelo->seFinalizoElJuego(true);
	modelo->seFinalizoElNivel(true);
	modelo->getDispatcher()->enviarMensaje( quit );
	modelo->getDispatcher()->join();
	std::cout<< "SE CERRO EL SERVIDOR...\n";	
	return false;
}
