#ifndef ACTUALIZARJUEGO_H_
#define ACTUALIZARJUEGO_H_

#include "Thread.h"
#include "Modelo.h"
#include "Mensaje.h"

class ActualizarJuego : public Thread
{
private:
	//Tiempo de actualizacion del juego en milisegundos
	int updateTime;
	//Determina si termino el nivel o no
	pBool finalizoNivel;
	
public:
	ActualizarJuego(pBool finalizoNivel);
	void main();
	/**
	 * Determina si el pacman colisiono con algun fantasma
	 */
	static bool chocaron();
	/**
	 * Determina se termino el nivel o no
	 */
	bool seFinalizoElNivel();
	/**
	 * Setea el comiezo o el fin del nivel.
	 */
	void seFinalizoElNivel(bool finalizo){*finalizoNivel=finalizo;};
	
	Mensaje* armarMensajeStatus();
};

#endif /*ACTUALIZARJUEGO_H_*/
