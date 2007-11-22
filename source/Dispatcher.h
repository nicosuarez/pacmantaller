///////////////////////////////////////////////////////////
//  Dispatcher.h
//  Implementation of the Class Dispatcher
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#if !defined(EA_15129548_CA1C_4143_A7FB_A6812DF62A1F__INCLUDED_)
#define EA_15129548_CA1C_4143_A7FB_A6812DF62A1F__INCLUDED_

/**
 * Clase engarda de despachar los mensajes a todos los jugadores..
 */
class Dispatcher
{

public:
	Dispatcher();
	virtual ~Dispatcher();

	void enviarMensajes();
	void main();

};
#endif // !defined(EA_15129548_CA1C_4143_A7FB_A6812DF62A1F__INCLUDED_)
