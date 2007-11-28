///////////////////////////////////////////////////////////
//  AceptarJugador.cpp
//  Implementation of the Class AceptarJugador
//  Created on:      21-Nov-2007 23:40:17
///////////////////////////////////////////////////////////

#include "AceptarJugador.h"

AceptarJugador::AceptarJugador(Socket* skServer,bool* finalizoJuego){
	this->skServer=skServer;
	*(this->finalizoJuego)=finalizoJuego;
}
/*----------------------------------------------------------------------------*/
AceptarJugador::~AceptarJugador(){

}
/*----------------------------------------------------------------------------*/
bool AceptarJugador::seFinalizoElJuego(){
	return *finalizoJuego;
}
/*----------------------------------------------------------------------------*/
Socket* AceptarJugador::aceptarJugador(){
	return this->skServer->aceptar();
}
/*----------------------------------------------------------------------------*/
/**
 * Hilo que se encarga de aceptar la conexion de un jugador nuevo
 */
void AceptarJugador::main(){

    while(!this->seFinalizoElJuego())
    {	
        //Acepta conexiones nuevas
    	Socket* scliente = this->aceptarJugador();
        if(!this->seFinalizoElJuego())
        {
            //Si se pudo conectar el cliente
            if(*scliente)
            {		
                /* Agrega el cliente a la lista */
                this->agregarJugador(scliente);
            }
        }
        else
        {
            delete scliente;
        }
    }	
    /* Libera las conexiones terminadas. Fin del juego */
}
/*---------------------------------------------------------------------------*/
void AceptarJugador::agregarJugador(Socket* scliente){
	
	//Creo un nuevo jugador
    Jugador* jugador=new Jugador(scliente);
    //Lo agrego a la lista de jugadores.
    ConnectionManager::getInstance()->agregarJugador(jugador);
}
/*---------------------------------------------------------------------------*/
AceptarJugador::operator bool() const {
    return (*this->skServer);		
}
