#include "ActualizarJuego.h"

ActualizarJuego* ActualizarJuego::pActualizarJuego = NULL;

ActualizarJuego* ActualizarJuego::getInstance () 
{
    if (pActualizarJuego == NULL)
    {  
    	pActualizarJuego = new ActualizarJuego(); 
    }
    return pActualizarJuego;
}

ActualizarJuego::ActualizarJuego(unsigned int updateTime)
{
	this->finalizoNivel=Modelo::getInstance()->getFinalizoNivel();
	this->updateTime=updateTime;
	std::cout<<"Construyo ActualizarJuego\n";
}

void ActualizarJuego::main()
{
	std::cout<<"Corre ActualizarJuego\n";
	while(!seFinalizoElNivel())
	{
		this->actualizar();
		sleep(updateTime);
		//Armar mensaje status
	}
	std::cout<<"Termino Actualizar Juego\n";
}
/*----------------------------------------------------------------------------*/
Mensaje* ActualizarJuego::armarMensajeStatus()
{
	//Chekear reglas del juego..
	
	//Termino el nivel?
	return NULL;
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::presionoKeyArriba(Jugador* jugador){
	//NOTA El jugador comienza en movimiento por alguna de las aristas que tiene
	//para salir.
	
	//Anula la tecla presionada anteriormente en caso de no haber podido efectuar
	//el movimiento de giro.
	this->avanzar(jugador);
	jugador->SetKeyPressed(NONE);
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::presionoKeyAbajo(Jugador* jugador){
	//Cambia la posicion 180, el personaje comienza a avanzar en la direccion
	//contraria
	Posicion* posicion = jugador->getPersonaje()->GetPosicion();
	
	std::cout<<"Inicial: " << *posicion;
	
	posicion->cambiarDireccion();

	//Cambio de vertice origen
	tVertice* vDest = this->getVeticeDestino(posicion);
	posicion->setVertice(vDest->getid());
	
	/*if(posicion->getPosicionArista()==FIN_ARISTA)
	{
		posicion->setPosicionArista(INICIO_ARISTA);
	}
	else if(posicion->getPosicionArista()==INICIO_ARISTA)
	{
		posicion->setPosicionArista(FIN_ARISTA);
	}*/
	
	jugador->SetKeyPressed(NONE);
	
	std::cout<<"Final: " << *posicion<<"\n";
}
/*----------------------------------------------------------------------------*/
tVertice* ActualizarJuego::getVeticeDestino(Posicion* posicion)
{
	Modelo* modelo = Modelo::getInstance();

	//Obtengo la arista actual.
	tArco* arcoActual=this->getAristaActual(posicion);
	
	//Obtengo el vertice destino
	int vDestId = arcoActual->getDestinoId();
	tVertice* vDest = modelo->GetMapa()->getGrafo()->getVertice(vDestId);
	return vDest;
}
/*----------------------------------------------------------------------------*/
tArco* ActualizarJuego::getAristaActual(Posicion* posicion)
{
	int vOrigId = posicion->getVertice();
	Modelo* modelo = Modelo::getInstance();
	
	//Obtener la arista actual
	tVertice* vOrig = modelo->GetMapa()->getGrafo()->getVertice(vOrigId);
	tArco* arcoActual = vOrig->getArco(posicion->getArista());
	return arcoActual;
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::presionoKeyIzquierda(Jugador* jugador){
	Posicion* posicion = jugador->getPersonaje()->GetPosicion();
	bool giro=false;
	int vOrigId = posicion->getVertice();
	Modelo* modelo = Modelo::getInstance();
	int aristaActualId =posicion->getArista();
		
	//Obtener la arista y vertice actual
	tVertice* vOrig = modelo->GetMapa()->getGrafo()->getVertice(vOrigId);
	tArco* arcoActual=NULL;
	/*if(aristaActualId!=0)
	{*/
		arcoActual = vOrig->getArco(aristaActualId);
//	}
	/*else
	{
		if(posicion->getDireccion()==S_O)
		{
			if(vOrig->getArco(Sur)!=NULL)
			{
				arcoActual=vOrig->getArco(Sur);
			}
			else if (vOrig->getArco(Oeste)!=NULL)
			{
				arcoActual=vOrig->getArco(Oeste);
			}
		}
		else if(posicion->getDireccion()==N_E)
		{
			if(vOrig->getArco(Norte)!=NULL)
			{
				arcoActual=vOrig->getArco(Norte);
			}
			else if (vOrig->getArco(Este)!=NULL)
			{
				arcoActual=vOrig->getArco(Este);
			}
		}
	}
*/

	 
	//Solo si el personaje esta en un vertice se permite realizar un giro.
	if(posicion->estaEnUnVertice() /*&& arcoActual!=NULL*/)
	{
		std::cout<<"Esta en un vertice\n";
		
		//En caso de venir por el Este, se obtiene la arista norte del vertice
		//destino
		if(arcoActual->getElemento()==Este)
		{
			tArco* arcoNuevo = vOrig->getArco(Norte);
			//Si no es pared (es decir tiene arista norte)
			//Si es pared se recuerda la tecla presionada, hasta gestionar el giro o 
			//anular el movimiento con la flecha para arriba siguiendo en la misma 
			//direccion, o hasta presionar otra tecla.
			if(arcoNuevo != NULL)
			{
				std::cout<<"Viene por el Este y gira hacia el Norte\n";
				//Actualizar Posicion
				girar(jugador,arcoNuevo,vOrigId,N_E);
				giro=true;
			}
			else
			{
				std::cout<<"Viene por el Este y hay PARED al Norte\n";
			}
		}
		//En caso de venir por el Norte, se obtiene la arista Oeste del vertice
		//destino
		else if(arcoActual->getElemento()==Norte)
		{
			tArco* arcoNuevo = vOrig->getArco(Oeste);
			if(arcoNuevo != NULL)
			{
				std::cout<<"Viene por el Norte y gira hacia el Oeste\n";
				//Actualizar Posicion
				girar(jugador,arcoNuevo,vOrigId,S_O);
				giro=true;
			}
			else
			{
				std::cout<<"Viene por el Norte y hay PARED al Oeste\n";
			}
		}
	
		//En caso de venir por el Oeste, se obtiene la arista Sur del vertice
		//destino
		else if(arcoActual->getElemento()==Oeste)
		{
			tArco* arcoNuevo = vOrig->getArco(Sur);
			if(arcoNuevo != NULL)
			{
				std::cout<<"Viene por el Oeste y gira hacia el Sur\n";
				//Actualizar Posicion
				girar(jugador,arcoNuevo,vOrigId,S_O);
				giro=true;
				
			}
			else
			{
				std::cout<<"Viene por el Oeste y hay PARED al Sur\n";
			}
		}
		//En caso de venir por el Sur, se obtiene la arista Este del vertice
		//destino
		else if(arcoActual->getElemento()==Sur)
		{
			tArco* arcoNuevo = vOrig->getArco(Este);
			if(arcoNuevo != NULL)
			{
				std::cout<<"Viene por el Sur y gira hacia el Este\n";
				//Actualizar Posicion
				girar(jugador,arcoNuevo,vOrigId,N_E);
				giro=true;
			}
			else
			{
				std::cout<<"Viene por el Sur y hay PARED al Este\n";
			}
		}
		
	}
	
	if(!giro)
	{
		std::cout<<"No puede doblar no llego al vertice o hay una pared\n";
		this->avanzar(jugador);
	}
	else
	{
		//Limpio el key presionado
		jugador->SetKeyPressed(NONE);
	}
		
}
/*----------------------------------------------------------------------------*/
/*Si es pared se recuerda la tecla presionada, hasta gestionar el giro o
 *anular el movimiento con la flecha para arriba siguiendo en la misma 
 *direccion, o hasta presionar otra tecla.
*/
void ActualizarJuego::presionoKeyDerecha(Jugador* jugador){
	Posicion* posicion = jugador->getPersonaje()->GetPosicion();
	tArco* arcoActual=this->getAristaActual(posicion);
	
	//Obtengo el vertice destino
	tVertice* vDest = this->getVeticeDestino(posicion); 
	int vDestId = vDest->getid();
	
	//Cuando llega al final de la arista se posiciona en el vertice 
	//destino. 
	if(posicion->estaEnUnVertice())
	{
		//En caso de venir por el Este, se obtiene la arista Sur del vertice
		//destino
		if(arcoActual->getElemento()==Este)
		{
			tArco* arcoNuevo = vDest->getArco(Sur);
			if(arcoNuevo != NULL)
			{
				//Actualizar Posicion (Cambio de vertice)
				girar(jugador,arcoNuevo,vDestId,S_O);
				
			}
		}
		//En caso de venir por el Norte, se obtiene la arista Este del vertice
		//destino
		else if(arcoActual->getElemento()==Norte)
		{
			tArco* arcoNuevo = vDest->getArco(Este);
			if(arcoNuevo != NULL)
			{
				//Actualizar Posicion (Cambio de vertice)
				girar(jugador,arcoNuevo,vDestId,N_E);
			}
		}
		//En caso de venir por el Oeste, se obtiene la arista Norte del vertice
		//destino
		else if(arcoActual->getElemento()==Oeste)
		{
			tArco* arcoNuevo = vDest->getArco(Norte);
			if(arcoNuevo != NULL)
			{
				//Actualizar Posicion (Cambio de vertice)
				girar(jugador,arcoNuevo,vDestId,N_E);
				
			}
		}
		//En caso de venir por el Sur, se obtiene la arista Este del vertice
		//destino
		else if(arcoActual->getElemento()==Sur)
		{
			tArco* arcoNuevo = vDest->getArco(Oeste);
			if(arcoNuevo != NULL)
			{
				//Actualizar Posicion (Cambio de vertice)
				girar(jugador,arcoNuevo,vDestId,S_O);
				
			}
		}
		
	}
		
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::girar(Jugador* jugador,tArco* arcoNuevo,
										int idVertice, int direccion)
{
	Posicion* posicion = jugador->getPersonaje()->GetPosicion();
	posicion->setVertice(idVertice);
	posicion->setArista(arcoNuevo->getid());
	posicion->setDireccion(direccion);
	
	if(direccion == N_E)
	{
		posicion->setPosicionArista(INICIO_ARISTA);
	}
	else if(direccion == S_O)
	{
		posicion->setPosicionArista(FIN_ARISTA);
	}

}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::salirDelJuego(){
	
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::noPresionoKey(Jugador* jugador){
	this->avanzar(jugador);
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::avanzar(Jugador* jugador){
	Posicion* posicion = jugador->getPersonaje()->GetPosicion();
	tArco* arcoActual=this->getAristaActual(posicion);
	Posicion posicionInicial = *posicion;  
	
	std::cout<<"Inicial: " << *posicion;
	
	//Si choco con una pared, no avanza mas y espera un giro.
	if(posicion->getArista()!=0)
	{	
		Personaje* personaje = jugador->getPersonaje();
		
		//Obtengo el vertice destino
		tVertice* vDest = this->getVeticeDestino(posicion); 
		int vDestId = vDest->getid();
		
		//Si el personaje va en direccion Este o Norte comienza en 0 y va aumentando
		if(posicion->getDireccion()==N_E)
		{
			posicion->setPosicionArista(posicion->getPosicionArista()+personaje->GetVelocidad());
		}
		//Si el personaje va en direccion Oeste o Sur comienza en 63 y va disminuyendo
		else if(posicion->getDireccion() == S_O)
		{
			posicion->setPosicionArista(posicion->getPosicionArista()-personaje->GetVelocidad());
		}
		
		//Si recorrio toda la arista, cambia de vertice
		//Y continua,en caso de tener, por la arista con la misma orientacion con la que
		//venia el personaje, si no se queda en el vertice
		if((posicion->getDireccion()==N_E && posicion->getPosicionArista()>=FIN_ARISTA) ||
			(posicion->getDireccion()==S_O && posicion->getPosicionArista()<=INICIO_ARISTA))
		{
			
			Orientacion orientacion = arcoActual->getElemento();
			tArco* arcoNuevo = vDest->getArco(orientacion);
			if(arcoNuevo != NULL)
			{
				//Actualizar Posicion
				int posArista = Posicion::getPosAristaInicial(posicion->getDireccion());
				int idArista = arcoNuevo->getid();
				posicion->SetPosicion(vDestId,idArista,posArista,posicion->getDireccion());
				
			}
			else
			{
				//Si hay una pared. Se queda en el vertice esperando a girar.

				*posicion = posicionInicial;
			}
			
		}
	}
	
	std::cout<<"  Final: " << *posicion <<"\n";
	
}
/*----------------------------------------------------------------------------*/
/**
 * Actualizar posicion de los jugadores
 */
void ActualizarJuego::actualizar()
{
	tListJugadores jugadores=Modelo::getInstance()->GetJugadores();
	itListJugadores it;
	int keyPressed=NONE;
	
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		
		Jugador* jugador = *it;
		keyPressed=jugador->GetKeyPressed();
		switch (keyPressed)
		{
			case KEY_ARRIBA:
				std::cout<<"Id:" << jugador->GetIdJugador() <<" "<< "Key:"<< "UP" <<"\n";
				presionoKeyArriba(jugador);
				break;
			case KEY_ABAJO:
				std::cout<<"Id:" << jugador->GetIdJugador() <<" "<< "Key:"<< "DOWN" <<"\n";
				presionoKeyAbajo(jugador);
				break;
			case KEY_IZQUIERDA:
				std::cout<<"Id:" << jugador->GetIdJugador() <<" "<< "Key:"<< "LEFT" <<"\n";
				presionoKeyIzquierda(jugador);
				break;
			case KEY_DERECHA:
				std::cout<<"Id:" << jugador->GetIdJugador() <<" "<< "Key:"<< "RIGHT" <<"\n";
				presionoKeyDerecha(jugador);
				break;
			case KEY_ESCAPE:
				std::cout<<"Id:" << jugador->GetIdJugador() <<" "<< "Key:"<< "ESC" <<"\n";
				salirDelJuego();
				break;
				
			default: //NONE
				std::cout<<"Id:" << jugador->GetIdJugador() <<" "<< "Key:"<< "NONE" <<"\n";
				noPresionoKey(jugador);
				break;
		}
		
	}
}

void ActualizarJuego::detectarColiciones()
{
	Modelo* modelo=Modelo::getInstance();
	tListJugadores jugadores=modelo->GetJugadores();
	itListJugadores it;
	
	//Comparo la posicion del pacman con la de cada fantasma.
	Posicion* posPacMan=modelo->getPacMan()->GetPosicion();
	
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		Jugador* jugador = *it;
		if(jugador->GetIdPersonaje()!=PacMan::PACMAN_TYPE)
		{
			Posicion* posFantasma = jugador->getPersonaje()->GetPosicion();
			if(estaDentroDelMargen(posPacMan,posFantasma))
			{
				
			}
		}
			
		
	}
}

//Valida si el pacman y el fantasma estan dentro del rango de colision.
bool ActualizarJuego::estaDentroDelMargen(Posicion* posPacman,Posicion* posFantasma)
{
	//posPacMan->
	return false;
}

bool ActualizarJuego::chocaron()
{
	int punt=Modelo::getInstance()->GetPuntuacion();
	std::cout<<punt;
	return true;
}

bool ActualizarJuego::seFinalizoElNivel()
{
	return *finalizoNivel;
}


