#include <iostream>
#include "Parser.h"
#include "Servidor.h"

int main(int argc,char* argv[])
{
	//Se validan los paramentros de entrada.
	Parser::validarParametros(argc);
		
	//Se carga el objeto singleton de configuracion del servidor.
	Parser::cargarConfiguracion(argv[1]);
	
	//Se insatancia el servidor y se pone a correr.
	Servidor server;
	return server.ejecutar();
}
