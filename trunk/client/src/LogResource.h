/* Clase LogResource
* Descripcion:
* Clase que provee los mensajes que se muestran al usuario
* y de los eventos que se muestran en el log.
*/

#ifndef LOG_RESOURCE_H_
#define LOG_RESOURCE_H_

#define MSG_SERVER_RUNNING "Servidor corriendo...\n"
#define MSG_SERVER_FINISH "Servidor finalizado.\n"
#define ERR_MAL_EJECUTADO 1
#define ERR_CONEXION_SOCKET 2
#define KEY_ESC 27
#define TTL_PACMAN "WaKa-WaKa 3D"
#define MSG_MAL_EJECUTADO_SVR "Modo de uso: ./server <archivo_configuracion.ini>\n"
#define BAJA_CLIENTE "BAJA_CLIENTE"
#define MSG_MAL_EJECUTADO_CLI "Modo de uso: ./client <IP host> <nro_puerto>\n"
#define MSG_SALIR_SERVER "Presione 'x' para salir..\n"
#define EXIT_KEY_SERVER "x"
#define MSG_NRO_CLIENTE "Jugador Nro: "
#define ERR_CARGANDO_TEXTURA "Error cargando textura\n"
#define TEX_PATH_PISO "piso.tga"
#define TEX_PATH_PARED "ladri.tga"

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
    
};

#endif
