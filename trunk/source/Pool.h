///////////////////////////////////////////////////////////
//  Pool.h
//  Implementation of the Class Pool
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_2E1EA99B_F3A4_4c99_BCEB_5DCFF9230684__INCLUDED_)
#define EA_2E1EA99B_F3A4_4c99_BCEB_5DCFF9230684__INCLUDED_

#include "Jugador.h"
#include <list>

typedef std::list<Jugador*> tListJugadores;

class Pool
{

public:
	Pool();
	virtual ~Pool();
	Jugador *m_Jugador;

	tListJugadores getJugadoresList();
	void setJugadoresList(tListJugadores jugadores);

private:
	/**
	 * Lista de jugadores conectados
	 */
	tListJugadores jugadoresList;

};
#endif // !defined(EA_2E1EA99B_F3A4_4c99_BCEB_5DCFF9230684__INCLUDED_)
