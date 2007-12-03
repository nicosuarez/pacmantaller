#include "Parser.h"

int Parser::getPuerto(string& arg){
	int port;
    
	/* Stream para formatear a entero */
	std::stringstream ps;
       
    /* Extrae la cadena del puerto y la pasa a entero */
	ps.str(arg);
	ps >> port;
	return port;			
}
/*----------------------------------------------------------------------------*/
void Parser::validarArgumentos(int argc,char* argv[],string* host,int* port)
{
	string argPort;
		
	if(argc==3)
	{
		*host=argv[1];
		argPort=argv[2];	
		*port = Parser::getPuerto(argPort);
	}	
	else
	{
		LogResource::mostrarModoEjecucionCliente();
		exit(ERR_MAL_EJECUTADO);
	}
}
