/* Clase Parser
* Descripcion:
* Clase que provee metodos para interpretar los argumentos de la aplicacion.
*/

#ifndef __CLIENT_PARSER_H__
#define __CLIENT_PARSER_H__

#include <string>
#include <sstream>
#include "LogResource.h"

using std::string;

class Parser
{
	public:
		/* Obtiene el puerto pasado por comando */
		static int getPuerto(string& arg);
		static void validarArgumentos(int argc,char* argv[],
									 string* host,int* port);
};

#endif
