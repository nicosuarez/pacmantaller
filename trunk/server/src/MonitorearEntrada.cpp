#include "MonitorearEntrada.h"

MonitorearEntrada::MonitorearEntrada(pBool cerrarServidor)
{
	this->cerrarServidor=cerrarServidor;
}

void MonitorearEntrada::main(){

	string entrada="";
	while(entrada!="x")
	{
		//El servidor se cierra cuando se presiona x.
		cin >> entrada;	
    }
	*cerrarServidor=true;
	std::cout<<"Agregar operacion CerrarServidorOp\n";
	Modelo::getInstance()->agregarOperacion(new CerrarServidorOp());
}
