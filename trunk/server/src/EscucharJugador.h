///////////////////////////////////////////////////////////
//  EscucharJugador.h
//  Implementation of the Class EscucharJugador
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_F9A636B0_BA80_4d07_AF20_62B177788D47__INCLUDED_)
#define EA_F9A636B0_BA80_4d07_AF20_62B177788D47__INCLUDED_

#include "Thread.h"
#include "Socket.h"
#include "Key.h"
#include "QuitarJugadorOp.h"
#include "Modelo.h"

/**
 * Hilo que se encarga de recibir los mensajes del server..
 */
class EscucharJugador: public Thread
{
private:
	//Id del jugador que recibe los mensajes
	int idJugador;
	
	//Socket del jugador
	Socket* socket;
	
	//Indica si finalizo el juego para saber si sigue escuchando al jugador
	bool *terminoJuego;
	
	//Recibe los mensajes del cliente
	int recibirMensaje();
	
public:
	//Constructor
	EscucharJugador( int idJugador, Socket* socket );
	
	//Destructor
	virtual ~EscucharJugador();
	
	//Recibe los mensajes que envia el cliente
	void main();
	

};
#endif // !defined(EA_F9A636B0_BA80_4d07_AF20_62B177788D47__INCLUDED_)
