#include "Request.h"

/******************************************************************************/
/* Implementacion */
/*------------------------------*/

Request::Request(const string& host,Socket::port_type puerto){
        /* Crea el socket con los datos pasados */
	this->skJugador = new Socket(host,puerto);
	this->recibirMensajes=NULL;
}
/*----------------------------------------------------------------------------*/
int Request::play(){
	int err=0;
     /* Si logro conectar */
	if(this->skJugador){
		this->recibirMensajes = new RecibirMensaje(this->skJugador);
		this->recibirMensajes->run();		
		this->recibirMensajes->join();
	}
	else
	{
		err = ERR_CONEXION_SOCKET;
	}
	return err;
}
/*----------------------------------------------------------------------------*/
Request::~Request(){
	delete (this->skJugador);
	delete this->recibirMensajes;
}

