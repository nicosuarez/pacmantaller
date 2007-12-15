#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

using std::string;

/**
 * Clase que contiene la configuracion del servidor.
 */
class Config
{

public:
	static Config* getInstance();
	static void setInstance(string mundoXmlPath,int port,int minJugadores,
			int maxJugadores,bool com_fantasmas,int vidas,string archivoLog);
	
protected:
	Config();
	Config(const Config&);
	Config& operator= (const Config&);
	Config(string mundoXmlPath,int port,size_t minJugadores,size_t maxJugadores,
	       bool com_fantasmas,int vidas,string archivoLog);
	
private:
	static Config* pConfig;
	/**
	 * Path del mundo en el que hay que jugar. 
	 */
	 string mundoXmlPath;
	/**
 	 * Puerto donde escucha las conexiones de los jugadores.
 	 */
 	int port;
	/** 
	 * Minima cantidad de jugadores para poder jugar simultaneamente.
	 */
	int minJugadores;
	/** 
	 * Maxima cantidad de jugadores para poder jugar simultaneamente.
	 */
	int maxJugadores;
	/** 
	 * Si esta activado, cuando un fantasma ve al Pac-Man, automaticamente 
	 * todos los demas fantasmas pueden verlo tambien.
	 */
	bool com_fantasmas;
	/** 
	 * Especifica la cantidad de veces que el pacman puede ser comido antes
	 * de perder el juego
	 */
	int vidas;
	/** 
	 * Archivo en el cual se escribe el reporte de actividades de los 
	 * clientes,de ser vacio se reportara a la salida estandar
	 * de perder el juego.
	 */
	string archivoLog;
	
public:
	/**
	 * Obtiene el Path del mundo en el que hay que jugar. 
	 */
	 string GetMundoXmlPath(){return this->mundoXmlPath;};
	/**
 	 * Obtiene el Puerto donde escucha las conexiones de los jugadores.
 	 */
 	int GetPort(){return this->port;};
	/** 
	 * Obtiene la Minima cantidad de jugadores para poder jugar simultaneamente.
	 */
 	size_t GetMinJugadores(){return this->minJugadores;};
	/** 
	 * Obtiene la Maxima cantidad de jugadores para poder jugar simultaneamente.
	 */
 	size_t GetMaxJugadores(){return this->maxJugadores;};
	/** 
	 * Si esta activado, cuando un fantasma ve al Pac-Man, automaticamente 
	 * todos los demas fantasmas pueden verlo tambien.
	 */
	bool GetComFantasmas(){return this->com_fantasmas;};
	/** 
	 * Especifica la cantidad de veces que el pacman puede ser comido antes
	 * de perder el juego
	 */
	int GetVidas(){return this->vidas;};
	/** 
	 * Obtiene el Archivo en el cual se escribe el reporte de actividades de los 
	 * clientes,de ser vacio se reportara a la salida estandar
	 * de perder el juego.
	 */
	string GetArchivoLog(){return this->archivoLog;};
	
};


#endif /*CONFIG_H_*/
