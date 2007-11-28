#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <string>
#include <stdlib.h>

#if defined(WIN32) || defined(__WIN32__)
#include <winsock2.h>
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#endif

class Socket
{
private:
    /* Datos de la conexion */
    struct sockaddr_in datos;
    /* Descriptor del socket */
    int fd;
    /* Indica si esta habilitado el socket */
    bool valido;
    #if defined(WIN32) || defined(__WIN32__)
        static int inst;
    #endif
public:
    typedef unsigned short port_type;
    /* Crea un socket que se conecta al servidor 'host', puerto 'port' */
    Socket(const std::string& host, port_type port);
    /* Crea un socket que escucha conexiones en el puerto 'port' */
    explicit Socket(port_type port, int backlog=5);
    /* Envia datos por el socket */
    int enviar(const std::string& buf);
    int enviar(const char* buf);
    /* Recibe datos del socket */
    int recibir(std::string& buf, size_t len);
    int recibir(char* buf,size_t len);
    /* Acepta una nueva conexion */
    Socket* aceptar();
    /* Para chequear si el socket es valido (por ej: if (socket) ...) */
    operator bool () const;
    /* Obtine el file descriptor del socket */
    int getFD () const {return this->fd;}
    /* Cierra y libera el socket */
    virtual ~Socket();

    /* Compara los fileDescriptor de los socket */
    bool operator==(const Socket &socket) const
    {
        return(this->fd == socket.fd );
    }
private:
    /* Constructor de copia y operator= ocultos (para prevenir descuidos)*/
    Socket(const Socket&);
    Socket& operator=(const Socket&);
    /* Crea un socket a partir de un file descriptor (para el accept) */
    Socket(int fd);
};

#endif

