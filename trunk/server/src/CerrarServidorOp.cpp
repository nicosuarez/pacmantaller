#include "CerrarServidorOp.h"

CerrarServidorOp::CerrarServidorOp()
{
}

bool CerrarServidorOp::ejecutar()
{
	Modelo *modelo = Modelo::getInstance();
	
	//Finalizar el juego.
	modelo->seFinalizoElJuego(true);
	modelo->seFinalizoElNivel(true);
	if( !modelo->GetJugadores().empty() )
	{
		//Enviar mensaje Quit a todos los jugadores
		Quit *quit = new Quit;
		modelo->getDispatcher()->enviarMensaje( quit );
	}
	modelo->getDispatcher()->getRecibiMensajeEvent().activar();
	modelo->getDispatcher()->join();
	std::cout<< "Se cerro el servidor...\n";	
	return true;
}

