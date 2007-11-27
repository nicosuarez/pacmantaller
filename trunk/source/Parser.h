/* Clase Parser
* Descripcion:
* Clase responsable de encapsular el manejo de archivos
*/

#ifndef __PARSER_H__
#define __PARSER_H__
#include <fstream>
#include <string>

#include "StrToken.h"
#include "Config.h"

#define ERR_MAL_EJECUTADO 2


class Parser
{
private:
    /* Atributos */
    static void cargarConfiguracion(tVecStr strTok);
    
public:

    /* Metodos */
    static void cargarConfiguracion(char* pathConfig);
    static void validarParametros(int cantParam);
};
#endif
