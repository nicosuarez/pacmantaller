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
string LogResource::getOrientacionContraria(string orientacion)
{
	if(orientacion == OESTE)
		return ESTE;
	if(orientacion == SUR)
		return NORTE;
	if(orientacion == NORTE)
		return SUR;
	if(orientacion == ESTE)
		return OESTE;
	return NORTE;
}

