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

ActualizarJuego::ActualizarJuego()
{
	this->finalizoNivel=Modelo::getInstance()->getFinalizoNivel();
	std::cout<<"Construyo ActualizarJuego\n";
}

ActualizarJuego::ActualizarJuego(pBool finalizoNivel)
{
	this->updateTime=100;
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
	jugador->SetKeyPressed(NONE);
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::presionoKeyAbajo(Jugador* jugador){
	//Cambia la posicion 180, el personaje comienza a avanzar en la direccion
	//contraria
	Posicion* posicion = jugador->getPersonaje()->GetPosicion();
	posicion->cambiarDireccion();
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::presionoKeyIzquierda(Jugador* jugador){
	Posicion* posicion = jugador->getPersonaje()->GetPosicion();
	int vOrigId = posicion->getVertice();
	Modelo* modelo = Modelo::getInstance();
	
	//Si presiona la tecla y no llego al fin de arista recuerda el giro.
	
	//Obtener la arista actual
	tVertice* vOrig = modelo->GetMapa()->getGrafo()->getVertice(vOrigId);
	tArco* arcoActual = vOrig->getArco(posicion->getArista());
	
	//Obtengo el vertice destino
	int vDestId = arcoActual->getDestinoId();
	tVertice* vDest = modelo->GetMapa()->getGrafo()->getVertice(vDestId);
	
	//Solo si el personaje esta en un vertice se permite realizar un giro.
	if(posicion->estaEnUnVertice())
	{
		//En caso de venir por el Este, se obtiene la arista norte del vertice
		//destino
		if(arcoActual->getElemento()==Este)
		{
			tArco* arcoNuevo = vDest->getArco(Norte);
			//Si no es pared (es decir tiene arista norte)
			//Si es pared se recuerda la tecla presionada, hasta gestionar el giro o 
			//anular el movimiento con la flecha para arriba siguiendo en la misma 
			//direccion, o hasta presionar otra tecla.
			if(arcoNuevo != NULL)
			{
				//Actualizar Posicion
				girar(jugador,arcoNuevo,vDestId,N_E);
				
			}
		}
		//En caso de venir por el Norte, se obtiene la arista Oeste del vertice
		//destino
		else if(arcoActual->getElemento()==Norte)
		{
			tArco* arcoNuevo = vDest->getArco(Oeste);
			if(arcoNuevo != NULL)
			{
				//Actualizar Posicion
				girar(jugador,arcoNuevo,vDestId,S_O);
			}
		}
	
		//En caso de venir por el Oeste, se obtiene la arista Sur del vertice
		//destino
		else if(arcoActual->getElemento()==Oeste)
		{
			tArco* arcoNuevo = vDest->getArco(Sur);
			if(arcoNuevo != NULL)
			{
				//Actualizar Posicion
				girar(jugador,arcoNuevo,vDestId,S_O);
				
			}
		}
		//En caso de venir por el Sur, se obtiene la arista Este del vertice
		//destino
		else if(arcoActual->getElemento()==Sur)
		{
			tArco* arcoNuevo = vDest->getArco(Este);
			if(arcoNuevo != NULL)
			{
				//Actualizar Posicion
				girar(jugador,arcoNuevo,vDestId,N_E);
				
			}
		}
		
	}
		
}
/*----------------------------------------------------------------------------*/
/*Si es pared se recuerda la tecla presionada, hasta gestionar el giro o
 *anular el movimiento con la flecha para arriba siguiendo en la misma 
 *direccion, o hasta presionar otra tecla.
*/
void ActualizarJuego::presionoKeyDerecha(Jugador* jugador){
	Posicion* posicion = jugador->getPersonaje()->GetPosicion();
	int vOrigId = posicion->getVertice();
	Modelo* modelo = Modelo::getInstance();
	
	//Si presiona la tecla y no llego al fin de arista recuerda el giro.
	
	//Obtener la arista actual
	tVertice* vOrig = modelo->GetMapa()->getGrafo()->getVertice(vOrigId);
	tArco* arcoActual = vOrig->getArco(posicion->getArista());
	
	//Obtengo el vertice destino
	int vDestId = arcoActual->getDestinoId();
	tVertice* vDest = modelo->GetMapa()->getGrafo()->getVertice(vDestId);
	
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
	
	//Limpio el key presionado
	jugador->SetKeyPressed(NONE);
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
	Personaje* personaje = jugador->getPersonaje();
	int vOrigId = posicion->getVertice();
	Modelo* modelo = Modelo::getInstance();
	
	//Obtener la arista actual
	tVertice* vOrig = modelo->GetMapa()->getGrafo()->getVertice(vOrigId);
	tArco* arcoActual = vOrig->getArco(posicion->getArista());
	
	//Obtengo el vertice destino
	int vDestId = arcoActual->getDestinoId();
	tVertice* vDest = modelo->GetMapa()->getGrafo()->getVertice(vDestId);
	
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
	if((posicion->getDireccion()==N_E && posicion->getPosicionArista()>FIN_ARISTA) ||
		(posicion->getDireccion()==S_O && posicion->getPosicionArista()<INICIO_ARISTA))
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
			//IdArista=0
			posicion->SetPosicion(vDestId,posicion->getDireccion());
		}
		
	}
	
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
				presionoKeyArriba(jugador);
				break;
			case KEY_ABAJO:
				presionoKeyAbajo(jugador);
				break;
			case KEY_IZQUIERDA:
				presionoKeyIzquierda(jugador);
				break;
			case KEY_DERECHA:
				presionoKeyDerecha(jugador);
				break;
			case KEY_ESCAPE:
				salirDelJuego();
				break;
				
			default: //NONE
				noPresionoKey(jugador);
				break;
		}
		
	}
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


