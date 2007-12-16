#include "MonitorearEntrada.h"

MonitorearEntrada::MonitorearEntrada(pBool cerrarServidor)
{
	this->cerrarServidor=cerrarServidor;
}

void MonitorearEntrada::main(){

	string entrada="";
	while( entrada != EXIT_KEY_SERVER )
	{
		//El servidor se cierra cuando se presiona x.
		cin >> entrada;	
    }
	*cerrarServidor = true;
	Modelo *modelo = Modelo::getInstance();
	std::cout<<"Agregar operacion CerrarServidorOp\n";
	modelo->getDispatcher()->enviarMensaje( new Stop(SERVER_TERMINADO) );
	modelo->agregarOperacion(new CerrarServidorOp());
	modelo->getEsperarMinJugadoresEvent().activar();
}
