#ifndef PLAY_H_
#define PLAY_H_

#include "Thread.h"
#include "Modelo.h"
#include "Start.h"
#include "Status.h"

class Play : public Thread
{
private:
	Jugador* jugador;
public:
	Play(Jugador* jugador);
	void main();
};

#endif /*PLAY_H_*/
