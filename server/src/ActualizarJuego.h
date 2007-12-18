#ifndef ACTUALIZARJUEGO_H_
#define ACTUALIZARJUEGO_H_

#include "Thread.h"
#include "Modelo.h"
#include "Coordenada.h"
#include "Key.h"
#include "CerrarServidorOp.h"
#include "Status.h"
#include "CambiarDeNivelOp.h"
#include "Timer.h"
#include "Stop.h"

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
	//Tiempo en ms que mantiene visible el bonus
	static const int tMantenerVisibleBonus = 30000;
	//Tiempo en ms que tarda en juego en agregar un bonus
	static const int tAgregarBonus = 60000;
	
	//Atributos para el manejo del envio de bonus.
	Timer agregarBonus;
	Timer mantenerVisible;
	Elemento* bonusActual;
	bool mantenerBonus;
	
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
	void analizarColision(PacMan* pacman,Jugador* fantasma);
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
	void desconectarJugador( int idJugador );
	void noPresionoKey(Jugador* jugador);
	static tVertice* getVeticeDestino(Posicion* posicion);
	static tArco* getAristaActual(Posicion* posicion);
	void doblarJugador(Jugador* jugador,bool izq);
	void ganoPacman();
	void cambiarDeNivel();
	void agregaBonusAlJuego();
	
	void enviarStatus();

	//Destructor
	~ActualizarJuego();
	
protected:
	ActualizarJuego(unsigned int updateTime=500);
	ActualizarJuego(const ActualizarJuego&);
	ActualizarJuego& operator= (const ActualizarJuego&);

};

#endif /*ACTUALIZARJUEGO_H_*/
