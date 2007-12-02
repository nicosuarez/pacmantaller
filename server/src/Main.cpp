#include <iostream>
#include "Parser.h"
#include "Servidor.h"

int main(int argc,char* argv[])
{
	//Se validan los paramentros de entrada.
	Parser::validarParametros(argc);
		
	//Se carga el objeto singleton de configuracion del servidor.
	Parser::cargarConfiguracion(argv[1]);
	
	//Se instancia el servidor y se pone a correr.
	Servidor server;
	int exit=server.ejecutar();
	return exit;
}
