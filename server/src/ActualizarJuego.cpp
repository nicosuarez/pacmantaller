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

ActualizarJuego::~ActualizarJuego()
{
	ActualizarJuego::pActualizarJuego = NULL;
}

ActualizarJuego::ActualizarJuego(unsigned int updateTime)
{
	this->finalizoNivel=Modelo::getInstance()->getFinalizoNivel();
	this->updateTime=updateTime;
	std::cout<<"Construyo ActualizarJuego\n";
	this->mantenerBonus=false;
	this->bonusActual=NULL;
}

void ActualizarJuego::esperarAgregarJugadores()
{
	if(Modelo::getInstance()->GetJugadores().empty())
		Modelo::getInstance()->getEsperarAgregarJugadores().esperar();
}

void ActualizarJuego::main()
{
	std::cout<<"Corre ActualizarJuego\n";
	
	this->esperarAgregarJugadores();
	
	while(!seFinalizoElNivel())
	{
		this->actualizar();
		this->enviarStatus();
		sleep(updateTime);
	}
	std::cout<<"Termino Actualizar Juego\n";
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::agregaBonusAlJuego()
{
	Modelo* modelo = Modelo::getInstance();
	Elemento* elemento=NULL;
	
	if(mantenerBonus)
	{
		elemento=this->bonusActual;
		elemento->setEstado(Visible);
	}
	else
		elemento=modelo->hayBonus();
			
	//Paso el tiempo
	if(agregarBonus.getTimeStartNow()>tAgregarBonus)
	{
		if(elemento!=NULL)
		{
			std::cout<<"agregar bonus.."<<elemento<<"\n";
			if(mantenerVisible.getTimeStartNow()<tMantenerVisibleBonus)
			{
				std::cout<<"Mantener visible bonus..\n";
				//MostrarBonus
				if(!mantenerBonus)
				{
					elemento->setEstado(Aparece);
					this->mantenerBonus=true;
					this->bonusActual=elemento;
				}
			}
			else
			{
				if(elemento->getEstado()!=Desaparece)
					elemento->setEstado(Desaparece);
				this->mantenerBonus=false;
				this->bonusActual=NULL;
				agregarBonus.initial();
				mantenerVisible.initial();
			}
		}
	}
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::enviarStatus()
{
	if( !seFinalizoElNivel() )
	{
		Status *status = new Status;
		Modelo::getInstance()->getDispatcher()->enviarMensaje( status);
		std::cout << "Envio Mensaje STATUS\n";
	}
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
	jugador->getPersonaje()->chocoConPared(false);
	
	jugador->SetKeyPressed(NONE);
	if(posicion->estaEnUnVertice())
		this->avanzar(jugador);
	
	std::cout<<"Final: " << *posicion<<"\n";
}
/*----------------------------------------------------------------------------*/
tVertice* ActualizarJuego::getVeticeDestino(Posicion* posicion)
{
	Modelo* modelo = Modelo::getInstance();

	//Obtengo la arista actual.
	tArco* arcoActual=ActualizarJuego::getAristaActual(posicion);
	
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
//Si es pared se recuerda la tecla presionada, hasta gestionar el giro o 
//anular el movimiento con la flecha para arriba siguiendo en la misma 
//direccion, o hasta presionar otra tecla.

void ActualizarJuego::presionoKeyIzquierda(Jugador* jugador){
	this->doblarJugador(jugador,true);
}
/*----------------------------------------------------------------------------*/
/*Si es pared se recuerda la tecla presionada, hasta gestionar el giro o
 *anular el movimiento con la flecha para arriba siguiendo en la misma 
 *direccion, o hasta presionar otra tecla.
*/
void ActualizarJuego::doblarJugador(Jugador* jugador,bool izq)
{
	Personaje* personaje = jugador->getPersonaje();
	Posicion* posicion = personaje->GetPosicion();
	Modelo* modelo = Modelo::getInstance();
	bool giro=false;
	int vOrigId = posicion->getVertice();
	int aristaActualId =posicion->getArista();
	
	//Obtener orientacion actual
	tVertice* vOrig = modelo->GetMapa()->getGrafo()->getVertice(vOrigId);	
	Orientacion oriActual = vOrig->getArco(aristaActualId)->getElemento();

	//Solo si el personaje esta en un vertice se permite realizar un giro.
	if(posicion->estaEnUnVertice())
	{	
		if(personaje->chocoConPared())
		{
			//Tomo el vertice Destino
			tVertice* vDest = this->getVeticeDestino(posicion); 
			giro = this->girar(jugador,vDest,oriActual,izq);
		}
		else
		{
			//Tomo el vertice actual
			giro = this->girar(jugador,vOrig,oriActual,izq);
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
void ActualizarJuego::presionoKeyDerecha(Jugador* jugador){
	this->doblarJugador(jugador,false);	
}
/*----------------------------------------------------------------------------*/
bool ActualizarJuego::girar(Jugador* jugador,tVertice* vertice
							,Orientacion oriActual,bool izq)
{
	bool giro=false;

	Personaje* personaje = jugador->getPersonaje();
	Posicion* posicion = personaje->GetPosicion();

	//Tomo el arcoNuevo
	Orientacion ori = Posicion::rotarDireccion(oriActual,izq);
	tArco* arcoNuevo = vertice->getArco(ori);

	if(arcoNuevo != NULL)
	{
		std::cout<<"Viene por el " << oriActual
				<<" y gira hacia el "<< ori <<"\n";
		//Actualizar Posicion
		posicion->setVertice(vertice->getid());
		posicion->setArista(arcoNuevo->getid());
		
		int direccion = Posicion::getDireccionInicial(ori);
		posicion->setDireccion(direccion);
		posicion->setPosicionArista(Posicion::getPosAristaInicial(direccion));

		giro=true;
		personaje->chocoConPared(false);
	}
	else
	{
		std::cout<<"Viene por el " << oriActual
				<< " y hay PARED al "<< ori <<"\n";
	}
		
	return giro;
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::desconectarJugador( int idJugador ){
	QuitarJugadorOp *quitarJugador = new QuitarJugadorOp( idJugador );
	Modelo::getInstance()->agregarOperacion( quitarJugador );
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::noPresionoKey(Jugador* jugador){
	this->avanzar(jugador);
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::avanzar(Jugador* jugador){
	Personaje* personaje = jugador->getPersonaje();
	Posicion* posicion = personaje->GetPosicion();
	tArco* arcoActual=this->getAristaActual(posicion);

	std::cout<<"Inicial: " << *posicion;
	
	//Si choco con una pared, no avanza mas y espera un giro.
	if(!personaje->chocoConPared())
	{	
		std::cout<<"Avanza: " ;
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
				int posArista = Posicion::getPosAristaFinal(posicion->getDireccion());
				posicion->setPosicionArista(posArista);
				personaje->chocoConPared(true);
			}
			
		}
	}
	
	std::cout<<"  Final: " << *posicion <<"\n";
	
}
/*----------------------------------------------------------------------------*/
/**
 * Actualizar posicion de los jugadores
 */
void ActualizarJuego::actualizarPosiciones()
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
				desconectarJugador( jugador->GetIdJugador() );
				break;
				
			default: //NONE
				std::cout<<"Id:" << jugador->GetIdJugador() <<" "<< "Key:"<< "NONE" <<"\n";
				noPresionoKey(jugador);
				break;
		}
	}
}
/*----------------------------------------------------------------------------*/
/**
 * Actualizar los elementos del juego
 */
void ActualizarJuego::actualizarElementos()
{
	Modelo* modelo = Modelo::getInstance();
	PacMan* pacman=modelo->getPacMan();
	pacman->comer();
}
/*----------------------------------------------------------------------------*/
/**
 * Actualizar Juego
 */
void ActualizarJuego::actualizar()
{
	this->actualizarPosiciones();
	this->agregaBonusAlJuego();
	this->actualizarElementos();
	this->detectarColisiones();
	//this->cambiarDeNivel();
	this->ganoPacman();
}
/*----------------------------------------------------------------------------*/
//Si el pacman comio todas las pastillas y powersUp gano el nivel
void ActualizarJuego::ganoPacman()
{
	Modelo *modelo = Modelo::getInstance();
	tListElementos* elementos = modelo->GetElementos();
	if(elementos->size() == 0)
	{
		//sleep(3000);
		std::cout<<"GANO PACMAN\n";
		modelo->getDispatcher()->enviarMensaje( new Stop(PACMAN_GANO) );
		this->cambiarDeNivel();
	}
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::cambiarDeNivel()
{
	//Operacion CambiarDeNivelOp
	CambiarDeNivelOp* cambiarNivel = new CambiarDeNivelOp();
	Modelo::getInstance()->agregarOperacion(cambiarNivel);
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::analizarColision(PacMan* pacman,Jugador* jugadorfantasma)
{
	if(pacman->IsPowerUp())
	{
		Personaje* personaje = jugadorfantasma->getPersonaje();
		Fantasma* fantasma = (Fantasma*)personaje;
		
		//Se muere el fantasma y retorna a la casa
		fantasma->irACasa();
		//el pacman incrementa su puntaje
		pacman->incPuntaje(fantasma->getPuntaje());
		
		std::cout<<"El fantasma:"<< jugadorfantasma->GetIdJugador() <<" fue comido\n";
	}
	else
	{
		Modelo *modelo = Modelo::getInstance();
		//Si el pacman fue comido finaliza el juego
		modelo->getDispatcher()->enviarMensaje( new Stop( PACMAN_FUE_COMIDO ) );
		modelo->agregarOperacion( new CerrarServidorOp() );
	}
}
/*----------------------------------------------------------------------------*/
void ActualizarJuego::detectarColisiones()
{
	Modelo* modelo=Modelo::getInstance();
	Mapa* mapa = modelo->GetMapa();
	tListJugadores jugadores=modelo->GetJugadores();
	itListJugadores it;
	
	//Comparo la posicion del pacman con la de cada fantasma.
	PacMan* pacman = modelo->getPacMan();
	Posicion* posPacMan=pacman->GetPosicion();
	
	for(it=jugadores.begin();it!=jugadores.end();it++)
	{
		Jugador* jugador = *it;
		if(jugador->GetIdPersonaje()!=PacMan::PACMAN_TYPE)
		{
			Fantasma* fantasma = (Fantasma*)jugador->getPersonaje();
			Posicion* posFantasma = fantasma->GetPosicion();
			if(Coordenada::calcularDistancia(posPacMan,posFantasma,mapa) < pacman->getRadio()+fantasma->getRadio())
			{
				std::cout<<"Chocaron\n";
				this->analizarColision(pacman,jugador);
			}
		}
	}
}
/*----------------------------------------------------------------------------*/
bool ActualizarJuego::seFinalizoElNivel()
{
	return *finalizoNivel;
}


