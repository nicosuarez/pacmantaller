///////////////////////////////////////////////////////////
//  ConnectionManager.h
//  Implementation of the Class ConnectionManager
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_9FD9E414_BBDB_43e0_8CD7_CFB519785B5B__INCLUDED_)
#define EA_9FD9E414_BBDB_43e0_8CD7_CFB519785B5B__INCLUDED_

#include "Pool.h"
#include "Jugador.h"
#include "Config.h"
#include "AgregarJugadorOp.h"

class ConnectionManager
{

public:
	static ConnectionManager* getInstance();

	void agregarJugador(Jugador* jugador);
	void enviarMensaje();
	Pool& GetPool();
	void quitarJugador(int idJugador);
	Jugador* getJugador(int idJugador);
	//Cantidad de jugadores conectados.
	int GetCantJugadores(){return this->cantJugadores;};
	void asignarIdJugador(Jugador* jugador);
	
	bool validarMinJugadores();
	bool validarMaxJugadores();
private:
	Pool pool;
    static ConnectionManager* pConnectionManager;
    //Asigna a los jugadores un id unico.
    int asignarId;
    //Maxima cantidad de jugadores
    int maxJugadores;
    //Minima cantidad de jugadores
    int minJugadores;
    //Cantidad de jugadores conectados.
    int cantJugadores;
    
protected:
	ConnectionManager();
    ConnectionManager(const ConnectionManager&);
    ConnectionManager& operator= (const ConnectionManager&);

};
#endif // !defined(EA_9FD9E414_BBDB_43e0_8CD7_CFB519785B5B__INCLUDED_)
