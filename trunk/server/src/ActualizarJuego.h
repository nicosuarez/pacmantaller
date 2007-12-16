#ifndef ACTUALIZARJUEGO_H_
#define ACTUALIZARJUEGO_H_

#include "Thread.h"
#include "Modelo.h"
#include "Coordenada.h"
#include "Key.h"
#include "CerrarServidorOp.h"
#include "Status.h"
#include "CambiarDeNivelOp.h"

class Fantasma;
class PacMan;

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
	void detectarColisiones();
	/**
	 * Determina si el pacman colisiono con algun fantasma
	 */
	void analizarColision(PacMan* pacman,Fantasma* fantasma);
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
	void actualizarPosiciones();
	void actualizarElementos();
	void esperarAgregarJugadores();
	
	
	bool girar(Jugador* jugador,tVertice* vertice, Orientacion orientacion,bool izq);
	
	void avanzar(Jugador* jugador);
	void presionoKeyArriba(Jugador* jugador);
	void presionoKeyAbajo(Jugador* jugador);
	void presionoKeyIzquierda(Jugador* jugador);
	void presionoKeyDerecha(Jugador* jugador);
	void desconectarJugador();
	void noPresionoKey(Jugador* jugador);
	static tVertice* getVeticeDestino(Posicion* posicion);
	static tArco* getAristaActual(Posicion* posicion);
	void doblarJugador(Jugador* jugador,bool izq);
	void ganoPacman();
	void cambiarDeNivel();
	
	void enviarStatus();

	//Destructor
	~ActualizarJuego();
	
protected:
	ActualizarJuego(unsigned int updateTime=5000);
	ActualizarJuego(const ActualizarJuego&);
	ActualizarJuego& operator= (const ActualizarJuego&);

};

#endif /*ACTUALIZARJUEGO_H_*/
