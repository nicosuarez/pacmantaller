#include <iostream>
#include "Parser.h"
#include "Cliente.h"

int main(int argc,char* argv[])
{
	int port=0,err=0;
	std::string host="";
	
	Parser::validarArgumentos(argc,argv,&host,&port);
	
	/* Crea un cliente para jugar */
	Cliente cliente(host,port);
	Socket *socket = cliente.getSocket();
	if( *socket ) //Verifica si se pudo conectar
	{
		/* Sale con el codigo de retorno correspondiente */
		err = cliente.ejecutar(argc,argv);
	}
	else
	{
		std::cout << "Servidor no disponible\n";
	}
	return err;	
}
