/* Clase Evento
* Descripcion:
* Permite poner a un hilo a la espera de una activación (evento) bajo ciertas
* condiciones.
*/

/* Metodos principales
* void activar():Activa el evento desbloqueando el hilo.
*
* void esperar():Se espera a que ocurrar la activacion de un evento..
*/

#ifndef EVENTO_H_
#define EVENTO_H_

#include <pthread.h>
#include "Mutex.h"

class Evento
{
private:
    pthread_cond_t condition; 	/* Condicion */
    pthread_mutex_t mutex_cond;	/* Mutex de la condicion*/
public:

    Evento()
    {
        /* Inicializa el mutex */
        pthread_mutex_init(&mutex_cond,NULL);
        /* Inicializa la condicion */
        pthread_cond_init(&condition,NULL);
    }

    void activar()
    {
        /* Activa el evento */
        pthread_cond_signal(&condition);
    }

    //Se espera a que ocurrar la activacion de un evento.  
    void esperar()
    {
        pthread_mutex_lock(&mutex_cond);
        pthread_cond_wait(&condition, &mutex_cond);
        pthread_mutex_unlock(&mutex_cond);
    }

    //Metodo que espera activacion.
    //Si se lockea previamente el mutex no se va a poder activar sin antes 
    //usar este metodo.
    void esperar(Mutex& mut_event)
    {
        pthread_cond_wait(&condition,&mut_event.getMutex());   
    }

    //Garantiza que activa solo si alguien se puso a esperar el evento.
    void activar(Mutex& mut_event)
    {
        pthread_mutex_lock(&mut_event.getMutex());
        pthread_cond_signal(&condition);
        pthread_mutex_unlock(&mut_event.getMutex());
    }

    virtual ~Evento()
    {
        pthread_mutex_destroy(&this->mutex_cond);
        pthread_cond_destroy(&this->condition);
    }

    /* Constructor de copia y operator ocultos */
    Evento(const Evento&);
    Evento& operator=(const Evento&);
};

#endif
