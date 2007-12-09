///////////////////////////////////////////////////////////
//  Jugador.h
//  Implementation of the Class Jugador
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_7A23278A_58F2_4d8e_BC8B_EFD82299567B__INCLUDED_)
#define EA_7A23278A_58F2_4d8e_BC8B_EFD82299567B__INCLUDED_

#include "EscucharJugador.h"
#include "Socket.h"
#include "Personaje.h"

/**
 * Clase que modela un jugador contiene el socket y instancia un hilo que se
 * encarga de escuchar los mensajes del servidor a traves de ese socket.
 * Tambien contiene un personaje asociado.
 */
class Jugador
{

public:
	Jugador(Socket* sk,int idPersonaje=-1,int idJugador=-1);
	virtual ~Jugador();
	EscucharJugador* escucharJugador;

	void escuchar();
	int GetIdJugador();
	int GetIdPersonaje();
	Personaje* getPersonaje();
	Socket* GetSocket();
	int GetKeyPressed();
	void SetIdJugador(int idJugador);
	void SetSocket(Socket* socket);
	void SetIdPersonaje(int idPersonaje);
	void SetPersonaje(Personaje* personaje);
	void SetKeyPressed(int keyPressed);
	
private:
	/**
	 * Identificador de jugador
	 */
	int idJugador;
	/**
	 * Socket mediante el cual el jugador mantiene la conexion con el servidor
	 */
	Socket* socket;
	/**
	 * Identificador de personaje
	 */
	int idPersonaje;
	/**
	 * Identificador de personaje
	 */
	Personaje* personaje;
	/**
	 * Tecla presionada por el jugador
	 */
	int keyPressed;

};
#endif // !defined(EA_7A23278A_58F2_4d8e_BC8B_EFD82299567B__INCLUDED_)
