/* Clase Timer
* Descripcion:
* La clase Timer la utiliza el modelo para establecer el tiempo en estado 
* powerup del pacman
*/

#ifndef _TIMER_H_
#define _TIMER_H_
#include <sys/time.h>
#include "StrToken.h"
#include <iostream>

using std::string;

class Timer
{
private:
    struct timeval tvinicial, tvactual;
    int cantdigitos;
    bool comenzo;

    /*Devuelve el tiempo medido en milisegundos*/
    int getmiliseg(struct timeval tv);

public:

    Timer(int cantdigitos=0);

    /*Inicializa el timer*/
    void initial();

    /*Devuelve el tiempo actual en formato int*/
    int getTime();

    /*Devuelve el tiempo actual en formato string*/
    std::string getTimeString();

    /*Devuelve el tiempo actual en formato string*/
    std::string convertToTime(int time);

    /*Devuelve el valor cero en formato string*/
    std::string getinitial();
};

#endif
