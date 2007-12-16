#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include <unistd.h>

class Thread {
private:
    pthread_t thread;

    enum State {
        initialState, sleepState, runState, finishState
    };

    State state;

public:
    /* Constructor queda a criterio de las subclases. */
    Thread(){state = initialState;};
    /* Lanza el thread */
    virtual void run();
    /* Pide al thread que finalice sus tareas lo antes posible */
    virtual void stop();
    /* Indica si el thread esta corriendo o no */
    virtual bool running() const;
    /* Indica si el thread esta dormido o no */
    virtual bool sleeping() const;
    /* Indica si el thread esta en state inicial*/
    virtual bool initial() const;
    /* Espera a que el thread termine realmente */
    virtual void join();
    /* Espera que el Thread termine y lo libera */
    virtual bool terminado()const;
    virtual ~Thread();
    /* Duerme el thread actual una cierta cantidad de milisegundos */
    static void sleep(unsigned long msecs);
    void cancelThread()
    {
    	pthread_cancel( this->thread);
    };
protected:
    /* Metodo virtual puro que deben implementar las subclases */
    virtual void main() = 0;
private:
    /* Metodo estatico (funcion plana) que realmente ejecuta el thread
    (tomar el puntero this como argumento siempre). */
    static void* static_run(void* arg);
    /* Constructor de copia y operator= ocultos (para prevenir descuidos) */
    Thread(const Thread&);
    Thread& operator=(const Thread&);
};

#endif
