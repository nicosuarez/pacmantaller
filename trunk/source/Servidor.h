///////////////////////////////////////////////////////////
//  Servidor.h
//  Implementation of the Class Servidor
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_)
#define EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_

/**
 * Clase que modela el servidor.
 */
class Servidor
{

public:
	Servidor();
	virtual ~Servidor();

private:
	/**
	 * Puerto donde escucha las conexiones de los jugadores.
	 */
	int port;

};
#endif // !defined(EA_14A2EC85_1217_49ba_9849_66D713CD39A6__INCLUDED_)
