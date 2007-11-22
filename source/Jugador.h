///////////////////////////////////////////////////////////
//  Jugador.h
//  Implementation of the Class Jugador
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_7A23278A_58F2_4d8e_BC8B_EFD82299567B__INCLUDED_)
#define EA_7A23278A_58F2_4d8e_BC8B_EFD82299567B__INCLUDED_

#include "EscucharJugador.h"
#include "Socket.h"

/**
 * Clase que modela un jugador contiene el socket y instancia un hilo que se
 * encarga de escuchar los mensajes del servidor a traves de ese socket.
 * Tambien contiene un personaje asociado.
 */
class Jugador
{

public:
	Jugador();
	virtual ~Jugador();
	EscucharJugador *m_EscucharJugador;

	void escuchar();
	int GetIdJugador();
	Socket* GetSocket();
	void SetIdJugador(int idJugador);
	void SetSocket(Socket* socket);

private:
	/**
	 * Identificador de jugador
	 */
	int idJugador;
	/**
	 * Socket mediante el cual el jugador mantiene la conexion con el servidor
	 */
	Socket* socket;

};
#endif // !defined(EA_7A23278A_58F2_4d8e_BC8B_EFD82299567B__INCLUDED_)
