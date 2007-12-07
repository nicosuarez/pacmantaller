/* Clase Parser
* Descripcion:
* Clase responsable de encapsular el manejo de archivos
*/

#ifndef __PARSER_H__
#define __PARSER_H__
#include <fstream>
#include <string>
#include <iostream>

#include "StrToken.h"
#include "Config.h"
#include "LogResource.h"
#include <map>

typedef std::map<std::string,std::string> tConf;

class Parser
{
private:
    /* Atributos */
    static void cargarConfiguracion(tConf config);
    static std::string strip(string s);
    
public:

    /* Metodos */
    static void cargarConfiguracion(char* pathConfig);
    static void validarParametros(int cantParam);
};
#endif
