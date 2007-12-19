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

string Parser::strip(string s)
{
	return s.substr(s.find_first_not_of(' '), s.find_last_not_of(' ')+1);
}
/*----------------------------------------------------------------------------*/
void Parser::cargarConfiguracion(char* pathConfig)
{
    ifstream fileConfig;
    string s = "";
  
    fileConfig.open(pathConfig);
    if(!fileConfig.fail())
    {          
    	  tConf conf;
		  while (getline(fileConfig, s))
		  {
		      if (s == EMPTY) // vacío
		              continue;
		      if (s[0] == '#') // comentario
		              continue;
		      if (s.find('=') == string::npos)
		      {
		    	  cerr << ERR_PARSER_CONIFG << "\n";
		    	  fileConfig.close();
		    	  exit(2);
		      }
		      string key = s.substr(0, s.find('='));
		      string val = s.substr(s.find('=')+1, string::npos);
		      conf[strip(key)] = strip(val);
		  }
		  cargarConfiguracion(conf);
    }
    else
    {
	    cerr << ERR_PARSER_CONFIG_FILE_NOT_FOUND << " " << pathConfig <<"\n";
	    fileConfig.close();
	    exit(3);
    }    	
    fileConfig.close();
}

/*----------------------------------------------------------------------------*/
void Parser::cargarConfiguracion(tConf config)
{
    string mundoXmlPath=EMPTY,archivoLog=EMPTY;
    int port=0,minJugadores=2,maxJugadores=5,vidas=1;
    bool com_fantasmas=false;

    mundoXmlPath=config[CFG_MUNDO];
    StrToken::stringTo<int>(port,config[CFG_PUERTO]);
    StrToken::stringTo<int>(minJugadores,config[CFG_MIN_JUGADORES]);
    StrToken::stringTo<int>(maxJugadores,config[CFG_MAX_JUGADORES]);
    StrToken::stringTo<int>(vidas,config[CFG_VIDAS]);
    StrToken::stringTo<bool>(com_fantasmas,config[CFG_COM_FANTASMAS]);
    archivoLog=config[CFG_LOG_FILE];
    
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
