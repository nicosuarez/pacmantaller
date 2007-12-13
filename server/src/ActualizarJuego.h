#ifndef ACTUALIZARJUEGO_H_
#define ACTUALIZARJUEGO_H_

#include "Thread.h"
#include "Modelo.h"
#include "PacMan.h"
#include "Key.h"

typedef bool* pBool;

class ActualizarJuego : public Thread
{
private:
	//Tiempo de actualizacion del juego en milisegundos
	int updateTime;
	//Determina si termino el nivel o no
	pBool finalizoNivel;
	//Rango de impacto entre las posiciones del los personajes
	int margenDeColicion;
	
	static ActualizarJuego* pActualizarJuego;
	
public:
	static ActualizarJuego* getInstance();

	void main();
	
	/**
	 * Verifica si hay coliciones o no.
	 */
	void detectarColiciones();
	/**
	 * Valida si el pacman y el fantasma estan dentro del rango de colision.
	 */
	bool estaDentroDelMargen(Posicion* posPacman,Posicion* posFantasma);
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
	/**
	 * Actualizar el juego analizando, reglas del juego y recalculando posiciones
	 */
	void actualizar();
	
	void girar(Jugador* jugador,tArco* arcoNuevo,
							int idVertice, int direccion);
	
	void avanzar(Jugador* jugador);
	void presionoKeyArriba(Jugador* jugador);
	void presionoKeyAbajo(Jugador* jugador);
	void presionoKeyIzquierda(Jugador* jugador);
	void presionoKeyDerecha(Jugador* jugador);
	void salirDelJuego();
	void noPresionoKey(Jugador* jugador);
	tVertice* getVeticeDestino(Posicion* posicion);
	tArco* getAristaActual(Posicion* posicion);
	
	Mensaje* armarMensajeStatus();

protected:
	ActualizarJuego(unsigned int updateTime=5000);
	ActualizarJuego(const ActualizarJuego&);
	ActualizarJuego& operator= (const ActualizarJuego&);

};

#endif /*ACTUALIZARJUEGO_H_*/
