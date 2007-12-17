#include "Timer.h"

/******************************************************************************/
/* Implementacion */
/*------------------------------*/

int Timer::getmiliseg(struct timeval tv)
{
    return ((tv.tv_sec*1000) + (tv.tv_usec/1000));
}
/*----------------------------------------------------------------------------*/
Timer::Timer(int cantdigitos)
{
    this->cantdigitos = cantdigitos;
    comenzo=false;
}
/*----------------------------------------------------------------------------*/	
void Timer::initial()
{
    gettimeofday( &tvinicial, 0 );
}
/*----------------------------------------------------------------------------*/
int Timer::getTime()
{
    gettimeofday( &tvactual, 0 );
    return ( getmiliseg(tvactual) - getmiliseg(tvinicial) );
}
/*----------------------------------------------------------------------------*/
int Timer::getTimeStartNow()
{
    if(!comenzo)
    {
        comenzo=true;
        this->initial();
        return 0;
    }
    gettimeofday( &tvactual, 0 );
    return ( getmiliseg(tvactual) - getmiliseg(tvinicial) );
}
/*----------------------------------------------------------------------------*/
string Timer::getTimeString()
{
    return convertToTime(getTime());
}
/*----------------------------------------------------------------------------*/
string Timer::convertToTime(int time)
{
    string tiempo = StrToken::intToString(time);
    int diferencia = cantdigitos - tiempo.size();
    if(diferencia<=0)
        return tiempo;
    for(int i=0; i< diferencia; i++ )
        tiempo = '0' + tiempo;
    return tiempo;
}
/*----------------------------------------------------------------------------*/
string Timer::getinitial()
{
    std::string initial = "0";
    for(int i=0; i< this->cantdigitos; i++ )
    {
        initial +='0';
    }
    return initial;
}
/*----------------------------------------------------------------------------*/
