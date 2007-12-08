#include "LogResource.h"

/******************************************************************************/
/* Implementacion */
/*------------------------------*/

void LogResource::mostrarServerStatus(bool on)
{
	if(on)
		std::cout<< MSG_SERVER_RUNNING;
	else
		std::cout<< MSG_SERVER_FINISH;
}
/*----------------------------------------------------------------------------*/
void LogResource::mostrarModoEjecucionCliente()
{
	std::cout<<MSG_MAL_EJECUTADO_CLI;
}
/*----------------------------------------------------------------------------*/
void LogResource::mostrarModoEjecucionServidor()
{
	std::cerr<<MSG_MAL_EJECUTADO_SVR;
}
/*----------------------------------------------------------------------------*/
void LogResource::mostrarSalirServer()
{
   	std::cout<<MSG_SALIR_SERVER;
}
/*----------------------------------------------------------------------------*/
string LogResource::getMsgNroCliente(string id)
{
	string mensaje="";
	mensaje= MSG_NRO_CLIENTE + id + "\n";
	return mensaje;
}
/*----------------------------------------------------------------------------*/
void LogResource::mostrarSeccion(string titulo)
{
	std::cout << "--- "<<titulo<<" ---" << std::endl;
}
/*----------------------------------------------------------------------------*/
void LogResource::mostrarKeyDesc(string keyDesc,string key,string desc)
{
	std::cout<<keyDesc<<":"<<key<<" "<< desc<< std::endl;;
}
/*----------------------------------------------------------------------------*/
void LogResource::mostrarKeyDesc(string keyDesc,int key,string desc)
{
	std::cout<<keyDesc<<":"<<key<<" "<< desc<< std::endl;;
}

