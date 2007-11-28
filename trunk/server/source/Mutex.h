/* Clase Mutex
* Descripcion
* Permite proteger secciones criticas de código, en un escenario concurrente 
* como por ejemplo los nodos.
*/ 

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>
#include <iostream>

class Mutex
{
private:
    pthread_mutex_t mutex;
public:
    /* Constructor */
    Mutex();
    /* Obtiene el mutex */
    int lock();
    /* Libera el mutex */
    int unlock();
    /* Destruye el mutex */
    ~Mutex();
    /* Destruye el mutex */
    pthread_mutex_t& getMutex(){return this->mutex;};

private:
    /* Constructor de copia y operator= ocultos */
    Mutex(const Mutex&);
    Mutex& operator=(const Mutex&);
};

#endif

