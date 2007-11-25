///////////////////////////////////////////////////////////
//  Modelo.h
//  Implementation of the Class Modelo
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#if !defined(EA_C452893E_00CB_470e_BB7D_F33E91B1347A__INCLUDED_)
#define EA_C452893E_00CB_470e_BB7D_F33E91B1347A__INCLUDED_

#include <list>
#include <queue>
#include "Elemento.h"
#include "Operacion.h"
#include "Personaje.h"
#include "AppSettings.h"

class Operacion;

typedef std::list<Elemento*> tListElementos;
typedef std::list<Personaje*> tListPersonajes; 
typedef std::queue<Operacion*> tQueueOperacion; 

/**
 * Clase que se controla el ciclo de vida del juego, aplicando diferentes
 * operaciones.
 */
class Modelo
{

public:
	Modelo();
	virtual ~Modelo();

	void agregarOperacion(Operacion* operacion);
	tListElementos GetElementos();
	tGrafo* GetMapa();
	tListPersonajes GetPersonajes();
	void main();
	void notify();
	void SetElementos(tListElementos elementos);
	void SetMapa(tGrafo* mapa);
	void SetPersonajes(tListPersonajes personajes);

private:
	/**
	 * Lista de elementos del mapa.
	 */
	tListElementos elementos;
	/**
	 * Nivel que se esta jugando actualmente.
	 */
	tGrafo* mapa;
	/**
	 * Lista de operacion que se ejecutan sobre el modelo
	 */
	tQueueOperacion operaciones;
	/**
	 * Lista de personajes puede ser PacMan o Fantasma
	 */
	tListPersonajes personajes;

};
#endif // !defined(EA_C452893E_00CB_470e_BB7D_F33E91B1347A__INCLUDED_)
