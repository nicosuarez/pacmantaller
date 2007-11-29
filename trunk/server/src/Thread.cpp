#include "Thread.h"
#include <iostream>

/******************************************************************************/
/* Implementacion */
/*------------------------------*/

void Thread::run(){
    if( this->state == initialState )
    {
        this->state = runState;
        pthread_create(&(this->thread),NULL,Thread::static_run,this);
    }
}
/*----------------------------------------------------------------------------*/
void Thread::stop(){
    pthread_yield();
}
/*----------------------------------------------------------------------------*/
bool Thread::running() const{
    if(this->state==runState)
        return true;
    else
        return false;	
}
/*----------------------------------------------------------------------------*/
bool Thread::sleeping() const
{
    if(this->state==sleepState)
        return true;
    else
        return false;	
}
/*----------------------------------------------------------------------------*/
bool Thread::initial() const
{
    if(this->state==initialState)
        return true;
    else
        return false;	
}
/*----------------------------------------------------------------------------*/
void Thread::join(){
    pthread_join(this->thread,NULL);
}
/*----------------------------------------------------------------------------*/
bool Thread::terminado()const
{
    return (this->state == finishState);
}
/*----------------------------------------------------------------------------*/
void Thread::sleep(unsigned long msecs){
    /* Como usleep recibe microsegundos, multiplico por 1000 */
    usleep(msecs*1000);
}
/*----------------------------------------------------------------------------*/
void* Thread::static_run(void* arg){
    Thread* th = (Thread*)arg;
    th->main();
    th->state = finishState;
    return (void*)0;
}
/*----------------------------------------------------------------------------*/
Thread::~Thread()
{
    this->stop();
    if(state != initialState && state != finishState)
    {
        pthread_cancel(this->thread);
    }
}
/*----------------------------------------------------------------------------*/
