///////////////////////////////////////////////////////////
//  EscucharJugador.h
//  Implementation of the Class EscucharJugador
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_F9A636B0_BA80_4d07_AF20_62B177788D47__INCLUDED_)
#define EA_F9A636B0_BA80_4d07_AF20_62B177788D47__INCLUDED_

#include "Thread.h"
#include "Socket.h"



/**
 * Hilo que se encarga de recibir los mensajes del server..
 */
class EscucharJugador: public Thread
{
private:
	Socket* sk_jugador;
public:
	EscucharJugador(Socket* sk_jugador);
	virtual ~EscucharJugador();

	void main();
	void recibirMensaje();

};
#endif // !defined(EA_F9A636B0_BA80_4d07_AF20_62B177788D47__INCLUDED_)
