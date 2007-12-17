/* Clase LogResource
* Descripcion:
* Clase que provee los mensajes que se muestran al usuario
* y de los eventos que se muestran en el log.
*/

#ifndef LOG_RESOURCE_H_
#define LOG_RESOURCE_H_

#define ERR_XML_MAPA "No se encuentra el mapa"
#define ERR_XML_MUNDO "No se encuentra el mundo"
#define MSG_SERVER_RUNNING "Servidor corriendo...\n"
#define MSG_SERVER_FINISH "Servidor finalizado.\n"
#define ERR_MAL_EJECUTADO 1
#define ERR_CONEXION_SOCKET 2
#define TTL_PACMAN "WaKa-WaKa 3D"
#define MSG_MAL_EJECUTADO_SVR "Modo de uso: ./server <archivo_configuracion.ini>\n"
#define BAJA_CLIENTE "BAJA_CLIENTE"
#define MSG_MAL_EJECUTADO_CLI "Modo de uso: ./client <IP host> <nro_puerto>\n"
#define MSG_SALIR_SERVER "Presione 'x' para salir..\n"
#define EXIT_KEY_SERVER "x"
#define MSG_NRO_CLIENTE "Jugador Nro: "
#define POWER_UP "PowerUp"
#define ELEMENTOS "Elementos"
#define ELEMENTO "Elemento"
#define ANCHO "Ancho"
#define ALTO "Alto"
#define ARISTA "Arista"
#define GRAFO "Grafo"
#define VERTICE "Vertice"
#define ATRIB_ID "id"
#define ATRIB_VALOR "valor"
#define PASTILLAS "Pastillas"
#define CASA_FANTASMAS "CasaFantasmas"
#define SALIDA_PACMAN "PacMan"
#define ATRIB_ORIENTACION "orientacion"
#define BONUS "Bonus"
#define ATRIB_TIPO "tipo"
#define ATRIB_ID_VERTICE "idv"
#define MAPA "Mapa" 
#define ATRIB_PATH "path"
#define ERR_PARSER_CONIFG "Error de parseo, no se encontró =" 
#define CFG_MUNDO "mundo"
#define CFG_PUERTO "puerto"
#define CFG_MIN_JUGADORES "minJugadores"
#define CFG_MAX_JUGADORES "maxJugadores"
#define CFG_VIDAS "vidas"
#define CFG_COM_FANTASMAS "com_fantasmas"
#define CFG_LOG_FILE "log_file"
#define CONFIGURACION "Configuracion"
#define ERR_PARSER_CONFIG_FILE_NOT_FOUND "No se pudo encontrar el archivo de configuracion"

#define OESTE "OESTE"
#define SUR "SUR"
#define NORTE "NORTE"
#define ESTE "ESTE"

#include <string>
#include <iostream>

using std::string;

class LogResource
{
public:
	/* Metodos */
    static void mostrarServerStatus(bool on);
    
    static void mostrarModoEjecucionCliente();
    
    static void mostrarModoEjecucionServidor();
    
    static void mostrarSalirServer();
    
    static string getMsgNroCliente(string id);
    
    static string getOrientacionContraria(string orientacion);
    
    static void mostrarSeccion(string titulo);
  
    static void mostrarKeyDesc(string keyDesc,string key,string desc);
    
    static void mostrarKeyDesc(string keyDesc,int key,string desc);

};

#endif
