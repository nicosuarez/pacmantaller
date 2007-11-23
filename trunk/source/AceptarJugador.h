///////////////////////////////////////////////////////////
//  AceptarJugador.h
//  Implementation of the Class AceptarJugador
//  Created on:      21-Nov-2007 23:40:17
///////////////////////////////////////////////////////////

#if !defined(EA_A409CB80_59B3_4ace_A341_2BE007BF9E0C__INCLUDED_)
#define EA_A409CB80_59B3_4ace_A341_2BE007BF9E0C__INCLUDED_

/**
 * Este thread se encarga de escuchar y aceptar los jugadores.
 */
class AceptarJugador
{

public:
	AceptarJugador();
	virtual ~AceptarJugador();

	
	void aceptarJugador();
	void main();

};
#endif // !defined(EA_A409CB80_59B3_4ace_A341_2BE007BF9E0C__INCLUDED_)
