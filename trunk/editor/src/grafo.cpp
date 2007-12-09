#include "grafo.h"

//Vertice

Vertice::Vertice(bool parOeste,bool parEste,bool parNorte,bool parSur,bool parConector):oeste(parOeste),este(parEste),norte(parNorte),sur(parSur),conector(parConector)
{
	id = -1;
}

void Vertice::setId(int parId)
{
	id = parId;
}

int Vertice::getId()
{
	return id;
}

//Indicadores de conexion existente

bool Vertice::conexionEste()
{
	return este;
}
bool Vertice::conexionOeste()
{
	return oeste;
}
bool Vertice::conexionNorte()
{
	return norte;
}
bool Vertice::conexionSur()
{
	return sur;
}
bool Vertice::esPortal()
{
	return conector;
}
//Grafo
Grafo::Grafo (int nroFilas,int nroColumnas):cantFilas(nroFilas),cantColumnas(nroColumnas)
{
}

int Grafo::agregarVertice(Vertice *V,int fila,int columna)
{
	//Nos fijamos si hay elementos alrededor del que queremos insertar. Debe ser posible conectar a cada elemento con el
	//que esta alrededor. Si no da ERROR y no inserta nada

	std::cout << "Actualizo G" << std::endl;//TODO

	std::list<RegArista> listaAux; //Lista de Aristas auxiliar

	int idV = fila*cantColumnas + columna;
	//Nos fijamos la conexion este
	if (V -> conexionEste() ) //Si es posible la conexion este
	{
		if ( (columna-1) < 0 ) //No hay nada para que se conecte por el este (precipisio)
		{
			if ( !(V -> esPortal()) ) //Es un vertice comun
				return ERROR;
			else
			{
				//Es un vertice que actua de portal
				int id = fila*cantColumnas + cantColumnas-1;
				if ( mapVertices[id] != 0 ) //Existe alguien para conectar
				{
					if ( !(mapVertices[id] -> conexionOeste()) ) //Si no es posible conectarlo
						return ERROR;
					RegArista R(id+fila*cantColumnas+cantColumnas,id,idV);
					listaAux.push_back(R);//Coloco la arista correspondiente
				}
				
			}
		}
		else
		{
			int id = fila*cantColumnas + (columna-1); //Calculo el id del vertice
			if ( mapVertices[id] != 0 ) //Existe alguien para conectar
			{
				if ( !(mapVertices[id] -> conexionOeste()) ) //Si no es posible conectarlo
					return ERROR;
				RegArista R(id+fila*cantColumnas+cantColumnas,id,idV);
				listaAux.push_back(R);//Coloco la arista correspondiente
			}
		}
	}
	//Nos fijamos la conexion oeste
	if (V -> conexionOeste() ) //Si es posible la conexion oeste
	{
		
		if ( (columna+1) >= cantColumnas ) //No hay nada para que se conecte por el oeste (precipisio)
		{
			if ( !(V -> esPortal()) )
				return ERROR;
			else
			{
				int id = fila*cantColumnas;
				if ( mapVertices[id] != 0 ) //Existe alguien para conectar
				{
					if ( !(mapVertices[id] -> conexionEste()) ) //Si no es posible conectarlo
						return ERROR;
					RegArista R(idV+fila*cantColumnas+cantColumnas,id,idV);
					listaAux.push_back(R);//Coloco la arista correspondiente
				}
			}
		}
		else
		{
			int id = fila*cantColumnas + (columna+1);
			if ( mapVertices[id] != 0 ) //Existe alguien para conectar
			{
				if ( !(mapVertices[id] -> conexionEste()) ) //Si no es posible conectarlo
					return ERROR;
				//columna++;
				RegArista R(id+fila*cantColumnas+cantColumnas-1,id,idV);
				listaAux.push_back(R);//Coloco la arista correspondiente
			}
		}
	}
	//Nos fijamos la conexion norte
	if (V -> conexionNorte() ) //Si es posible la conexion norte
	{
		if ( (fila-1) < 0 ) //No hay nada para que se conecte por el norte (precipisio)
		{
			if ( !(V -> esPortal()) )
				return ERROR;
			else
			{
				//Es un vertice que actua de portal
				int id = (cantFilas-1)*cantColumnas + columna;
				if ( mapVertices[id] != 0 ) //Existe alguien para conectar
				{
					if ( !(mapVertices[id] -> conexionSur()) ) //Si no es posible conectarlo
						return ERROR;
					RegArista R((0*cantColumnas)+columna+0*cantColumnas,id,idV);
					listaAux.push_back(R);//Coloco la arista correspondiente
				}
			}
		}
		else
		{
			int id = (fila-1)*cantColumnas + columna;
			if ( mapVertices[id] != 0 ) //Existe alguien para conectar
			{
				if ( !(mapVertices[id] -> conexionSur()) ) //Si no es posible conectarlo
					return ERROR;
				RegArista R(id+(fila-1)*cantColumnas+cantColumnas*2,id,idV);
				listaAux.push_back(R);//Coloco la arista correspondiente
			}
		}
	}
	//Nos fijamos la conexion sur
	if ( V -> conexionSur() ) //Si es posible la conexion sur
	{
		if ( (fila+1) >= cantFilas ) //No hay nada para que se conecte por el sur (precipisio)
		{
			if ( !(V -> esPortal()) )
				return ERROR;
			else
			{
				//Es un vertice que actua de portal
				int id = 0*cantColumnas + columna;
				if ( mapVertices[id] != 0 ) //Existe alguien para conectar
				{
					if ( !(mapVertices[id] -> conexionNorte()) ) //Si no es posible conectarlo
						return ERROR;
					RegArista R((0*cantColumnas)+columna+0*cantColumnas,id,idV);
					listaAux.push_back(R);//Coloco la arista correspondiente
				}
			}
		}
		else
		{
			int id = (fila+1)*cantColumnas + columna;
			if ( mapVertices[id] != 0 ) //Existe alguien para conectar
			{
				if ( !(mapVertices[id] -> conexionNorte()) ) //Si no es posible conectarlo
					return ERROR;
				RegArista R(id+(fila+1)*cantColumnas,id,idV);
				listaAux.push_back(R);//Coloco la arista correspondiente
			}
		}
		
	}
	//Si no ha habido errores se agrega el vertice y las correspondiente aristas
	V -> setId (idV);
	mapVertices[idV] = V;
	for (std::list<RegArista>::iterator it = listaAux.begin() ; it != listaAux.end() ; it++ )
		listaDeAristas.push_back(*it);

	//std::cout << "Al final las conexiones encontradas son: " << listaAux.size() << std::endl;//TODO

	return EXITO;
	
}

void Grafo::eliminarVertice(int fila,int columna)
{
	int id = fila*cantColumnas + columna;
	Vertice *V = mapVertices[id];

	//Borro las aristas
	if (V -> conexionEste() )
	{
		RegArista R(id+fila*cantColumnas+cantColumnas-1,0,0);
		listaDeAristas.remove(R);
	}
	if (V -> conexionOeste() )
	{
		RegArista R(id+fila*cantColumnas+cantColumnas,0,0);
		listaDeAristas.remove(R);
	}
	if (V -> conexionNorte() )
	{
		RegArista R(id+fila*cantColumnas,0,0);
		listaDeAristas.remove(R);
	}
	if ( V -> conexionSur() )
	{
		RegArista R(id+fila*cantColumnas+2*cantColumnas,0,0);
		listaDeAristas.remove(R);
	}
	delete V;
	mapVertices[id] = 0;
}

std::list<RegArista> Grafo::getListaDeAristas()
{
	return(listaDeAristas);
}

bool Grafo::grafoValido(std::string &mensajeError)
{
	//Comprueba que el grafo no contenga islas o precipicios
	
	//Comprueba que no haya precipicios
	for (int f = 0 ; f < cantFilas ; f++ )
		for (int c = 0 ; c < cantColumnas ; c++ )
		{
			int id = f*cantColumnas + c;
			if ( mapVertices[id] != 0 )
				if ( !(mapVertices[id] -> esPortal()) )
				{
					std::string orientacion;
					if ( (mapVertices[id] -> conexionEste()) && (mapVertices[id-1] == 0) )
						orientacion = "Este";
					if ( (mapVertices[id] -> conexionOeste()) && (mapVertices[id+1] == 0) )
						orientacion = "Oeste";
					if ( (mapVertices[id] -> conexionNorte()) && (mapVertices[(f-1)*cantColumnas+c] == 0) )
						orientacion = "Norte";
					if ( (mapVertices[id] -> conexionSur()) && (mapVertices[(f+1)*cantColumnas+c] == 0) )
						orientacion = "Sur";
					
					if ( !(orientacion.empty()) )
					{
						//Hay un error
						std::ostringstream cajaF,cajaC;
						
						cajaF << f;
						cajaC << c;
						mensajeError = "No existe conexion ";
						mensajeError += orientacion;
						mensajeError += " para el vertice: ";
						mensajeError += cajaF.str();
						mensajeError += ":";
						mensajeError += cajaC.str();
						return false;
					}
				}
		}
		
	//Comprueba que no hay islas
	return true;
}

//Destructor
Grafo::~Grafo()
{
	for (int f = 0 ; f < cantFilas ; f++ )
		for (int c = 0 ; c < cantColumnas ; c++ )
		{
			int id = f*cantColumnas + c;
			if ( mapVertices[id] != 0 )
				delete mapVertices[id];
		}
}

//-----------TODO------------------------------------
void Grafo::imprimirGrafo()
{
	std::cout << "Vertices : " << std::endl;
	for (int f = 0 ; f < cantFilas ; f++ )
		for (int c = 0 ; c < cantColumnas ; c++ )
		{
			if (mapVertices[f*cantColumnas+c] != 0)
				std::cout << "idV :" << mapVertices[f*cantColumnas+c] -> getId() << std::endl;
		}

	std::cout << "Columnas: " << std::endl;
	for (std::list<RegArista>::iterator it = listaDeAristas.begin() ; it != listaDeAristas.end() ; it++)
	{
		int a,v1,v2;
		it -> get(a,v1,v2);
		std::cout << "idC: " << a << " idV1: "<< v1 << " idV2: " << v2 << std::endl;
	}	
}
//----------TODO-------------------------------------
