/* Parser
* Implementacion Independiente
* Archivo : parser.cpp
* Version : 2.0
*/

#include "Parser.h"
#define EMPTY ""


/******************************************************************************/
/* Implementacion */
/*------------------------------*/

using namespace std;
/*----------------------------------------------------------------------------*/
void Parser::cargarConfiguracion(char* pathConfig)
{
    ifstream fileConfig;
    string linea = "";
  
    fileConfig.open(pathConfig);
    if(!fileConfig.fail())
    {
        while(!fileConfig.eof())
        {
            std::getline(fileConfig,linea);
            
            std::cout<<"Linea\n";
            std::cout<<linea;
            
            //Se ignoran las lineas vacias.
            if(linea!=EMPTY)
            {
            	std::cout<<linea;
                tVecStr strTok=StrToken::getStrTokens(linea,";");
                
                cargarConfiguracion(strTok);
            }
            linea=EMPTY;
        }
    }
    fileConfig.close();
}

/*----------------------------------------------------------------------------*/
void Parser::cargarConfiguracion(tVecStr strTok)
{
    string mundoXmlPath=EMPTY,archivoLog=EMPTY;
    int port=0,minJugadores=2,maxJugadores=5,vidas=1;
    bool com_fantasmas=false;

    StrToken::setTokensParams(strTok,"sdddbds",&mundoXmlPath,&port,
        &minJugadores,&maxJugadores,&com_fantasmas,
        &vidas,&archivoLog);
    
    //Se setea el objecto singleton de configuracion.
    Config::setInstance(mundoXmlPath,port,minJugadores,
    		maxJugadores,com_fantasmas,vidas,archivoLog);
}
/*----------------------------------------------------------------------------*/
void Parser::validarParametros(int cantParam)
{
	if(cantParam!=2)
    {
        std::cout<<"Cantidad de parametros invalido.\n";
        exit(ERR_MAL_EJECUTADO);
    }
}
