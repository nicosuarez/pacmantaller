#include "Socket.h"

/******************************************************************************/
/* Implementacion */
/*------------------------------*/

#if defined(WIN32) || defined(__WIN32__)
int Socket::inst = 0;
#endif

Socket::Socket(const std::string& host, port_type port){
    /* Estructura para datos de host */
    struct hostent *he;
    valido = true;
    /* Si es windows, inicializa Winsock */
        #if defined(WIN32) || defined(__WIN32__)
            if (Socket::inst == 0){
                WSAData wsaData;
                WSAStartup(MAKEWORD(1, 1), &wsaData);
            }
        #endif
    /* Obtener datos por nombre de host o ip */
    he = gethostbyname(host.c_str());
    /* Carga de datos para conexion */
    datos.sin_family = AF_INET;
    datos.sin_port = htons(port);
    datos.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(datos.sin_zero), 0, sizeof(int));
    /* Obtencion del socket */
    fd = socket(AF_INET,SOCK_STREAM,0);
    if (fd < 0) valido = false;
    /* Conexion al servidor */
    if ( connect(fd,(struct sockaddr *)&datos,sizeof(struct sockaddr)) < 0)
        valido = false;
    #if defined(WIN32) || defined(__WIN32__)
        Socket::inst++;
    #endif
}
/*----------------------------------------------------------------------------*/
Socket::Socket(port_type port, int backlog){
    valido = true;
        #if defined(WIN32) || defined(__WIN32__)
            if (Socket::inst == 0){
                WSAData wsaData;
                WSAStartup(MAKEWORD(1, 1), &wsaData);
            }
        #endif
    /* Datos del servidor */
    memset((char *)&datos,0, sizeof(datos));
    datos.sin_family = AF_INET;
    datos.sin_port = htons(port);
    datos.sin_addr.s_addr = INADDR_ANY;
    /* Obtencion del socket */
    fd = socket(AF_INET,SOCK_STREAM,0);
    if (fd<0) valido = false;
    /* Permite que podamos reutilizar la dirección IP de la maquina */
    int yes = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    /* Bindeo de puerto */
    if ( bind(fd,(struct sockaddr *)&datos,sizeof(struct sockaddr) ) < 0)
        valido = false;
    /* Pone el servidor a escuchar por conexiones */
    if ( listen(fd,backlog) < 0 ) valido = false;
        #if defined(WIN32) || defined(__WIN32__)
            Socket::inst++;
        #endif
}
/*----------------------------------------------------------------------------*/
Socket::Socket(int fd){
    valido = true;
    this->fd = fd;
    if (this->fd < 0) valido = false;
        #if defined(WIN32) || defined(__WIN32__)
            Socket::inst++;
        #endif
}
/*----------------------------------------------------------------------------*/
Socket* Socket::aceptar(){
    /* Variables auxiliares para el nuevo socket */
    Socket* r;
    int nfd;
    struct sockaddr_in ndatos;
    /* Si es windows, cambia el tipo de dato para la longitud */
        #if defined(WIN32) || defined(__WIN32__)
            int nlen = sizeof(ndatos);
        #else
            socklen_t nlen = (socklen_t)sizeof(ndatos);
        #endif
    /* Acepta la conexion */
    nfd = accept(this->fd,(struct sockaddr*)&ndatos,&nlen);
    /* Devuelve un nuevo socket listo para enviar y recibir */
    r = new Socket(nfd);
    return r;
}
/*----------------------------------------------------------------------------*/
int Socket::enviar(const std::string& buf){
	size_t bytesEnviados = 0;
	while( bytesEnviados < buf.size() && bytesEnviados >= 0 )
	{
		bytesEnviados += send( this->fd, buf.c_str() + bytesEnviados, buf.size()-bytesEnviados,0);
	}
    return bytesEnviados;
}
/*----------------------------------------------------------------------------*/
int Socket::recibir( std::string& buf, size_t size ){
    char* rec = new char[size+1];
    size_t bytesRecibidos=0;
    while( bytesRecibidos < size && bytesRecibidos >= 0 )
    {
    	bytesRecibidos += recv( this->fd, rec + bytesRecibidos,size-bytesRecibidos, 0 );
    }
    buf = rec;
    delete[] rec;
    return bytesRecibidos;
}
/*----------------------------------------------------------------------------*/
int Socket::enviar(const char* buf, size_t size){
	size_t bytesEnviados = 0;
	while( bytesEnviados < size && bytesEnviados >= 0 )
	{
		bytesEnviados += send( this->fd, buf + bytesEnviados , size-bytesEnviados , 0 );
	}
    return bytesEnviados;
}
/*----------------------------------------------------------------------------*/
int Socket::recibir(char* buf,size_t size){
    size_t bytesRecibidos = 0;
    while( bytesRecibidos < size  && bytesRecibidos >= 0 )
    {
    	bytesRecibidos += recv( this->fd, buf + bytesRecibidos, size-bytesRecibidos, 0 );
    }
    return bytesRecibidos;
}
/*----------------------------------------------------------------------------*/
Socket::operator bool() const{
    return this->valido;
}
/*----------------------------------------------------------------------------*/
Socket::~Socket(){
    /* Si es windows, cambia la forma de cierre */
        #if defined(WIN32) || defined(__WIN32__)
            Socket::inst--;
            closesocket(this->fd);
            if(Socket::inst == 0) WSACleanup();
        #else
            close(this->fd);	    
        #endif
}
