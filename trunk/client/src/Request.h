/* Clase Request
* Descripcion:
* Establece conexion con el servidor, y mantiene la conversacion con el mismo.
*/

#ifndef __CLIENT_PEDIDO_H__
#define __CLIENT_PEDIDO_H__

#include <iostream>
#include <string>
#include <fstream>
#include "Socket.h"
#include "LogResource.h"
#include "RecibirMensaje.h"

using std::string;

class Request {
	private:
		Socket* skJugador;
		int jugadorId;
		RecibirMensaje* recibirMensajes;
		
	public:
        /* Constructor conecta al servidor */
		Request(const string& host,Socket::port_type puerto);
        /* Envia los comandos al servidor y obtiene el resultado.
           Devuelve el codigo correspondiente si hubo error o 0 */
		int play();
        /* Destructor libera el socket */
		virtual ~Request();
};

#endif

