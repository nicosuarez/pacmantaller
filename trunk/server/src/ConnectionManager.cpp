///////////////////////////////////////////////////////////
//  ConnectionManager.cpp
//  Implementation of the Class ConnectionManager
//  Created on:      21-Nov-2007 23:40:18
///////////////////////////////////////////////////////////

#include "ConnectionManager.h"


ConnectionManager* ConnectionManager::pConnectionManager = NULL;

ConnectionManager* ConnectionManager::getInstance () 
{
    if (pConnectionManager == NULL)
    {  
    	pConnectionManager = new ConnectionManager(); 
    }
    return pConnectionManager;
}
/*----------------------------------------------------------------------------*/
ConnectionManager::ConnectionManager() 
{ 
   this->maxJugadores=Config::getInstance()->GetMaxJugadores();
   this->minJugadores=Config::getInstance()->GetMinJugadores();
   this->asignarId=0;
   this->cantJugadores=0;
}
/*----------------------------------------------------------------------------*/

void ConnectionManager::agregarJugador(Jugador* jugador){
	std::cout<<"Agregar Nuevo Jugador\n";
	//Incrementa la cantidad de jugadores conectados.
	this->cantJugadores++;
	std::cout<<"Cantidad de jugadores "<<cantJugadores<<"\n";
	
	//Se asigna un id unico al jugador
	this->asignarIdJugador(jugador);
	std::cout<<"Jugador nuevo id: "<<jugador->GetIdJugador()<<"\n";

	//Se pone a escuchar el socket del jugador
	jugador->escucharJugador->run();
	std::cout<<"escuchar jugador...\n";
	
	//AgregarJugadorOp Operacion
	Operacion* operacion = new AgregarJugadorOp(jugador);
	std::cout<<"Se crea operacion AGREGAR...\n";
	
	//Agrego la operacion al modelo
	Modelo::getInstance()->agregarOperacion(operacion);
	std::cout<<"Se agrega la operacion AGREGAR...\n";
	
	//Validar cantidad minima de jugadores para poder jugar.
    if(this->validarMinJugadores())
	{
    	//Empezar el nivel.
    	std::cout<<"Empezar Nivel...\n";
    	Modelo::getInstance()->getEsperarMinJugadoresEvent().activar();
	}
}
/*----------------------------------------------------------------------------*/
void ConnectionManager::enviarMensaje(){

}
/*----------------------------------------------------------------------------*/
Pool& ConnectionManager::GetPool(){
	return pool;
}
/*----------------------------------------------------------------------------*/
void ConnectionManager::quitarJugador(int idJugador){
	
	tListJugadores jugadores=this->pool.getJugadoresList();
	itListJugadores it;
	
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		Jugador* jugador = *it;
		if(jugador->GetIdJugador()==idJugador)
		{
			jugadores.erase(it);
		}
	}
}
/*----------------------------------------------------------------------------*/
Jugador* ConnectionManager::getJugador(int idJugador)
{
	tListJugadores jugadores=this->pool.getJugadoresList();
	itListJugadores it;
	Jugador* jugador=NULL;
	
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		if((*it)->GetIdJugador()==idJugador)
		{
			jugador=(*it);
			break;
		}
	}
	return jugador;
}
/*----------------------------------------------------------------------------*/
bool ConnectionManager::validarMinJugadores()
{
	if(this->cantJugadores < this->minJugadores)
	{
		return false;
	}
	else
	{
		return true;
	}
}
/*----------------------------------------------------------------------------*/
bool ConnectionManager::validarMaxJugadores()
{
	if(this->cantJugadores > this->maxJugadores)
	{
		return false;
	}
	else
	{
		return true;
	}
}
/*----------------------------------------------------------------------------*/
void ConnectionManager::asignarIdJugador(Jugador* jugador)
{
	//Se le asigna un id unico.
	jugador->SetIdJugador(this->asignarId);
	//Se incrementa el id para asignar al proximo jugador.
	this->asignarId++;
}

