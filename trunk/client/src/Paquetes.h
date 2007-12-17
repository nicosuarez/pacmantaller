#ifndef PAQUETES_H_
#define PAQUETES_H_

#ifdef __GNUC__
#define PACKED __attribute__((__packed__))
#else
#error Debe compilar con GCC
#endif

#include <stdint.h>

#define PACMAN_GANO 0
#define PACMAN_FUE_COMIDO 1
#define PACMAN_SE_DESCONECTO 2
#define JUGADORES_INSUFICIENTES 3
#define SERVER_TERMINADO 4

typedef struct PktCabecera
{
	uint8_t version: 2;
	uint8_t tipo: 3;
	uint8_t aux: 3;
}PACKED;

typedef struct PktInit
{
	//cabecera
	uint8_t version: 2;
	uint8_t tipo: 3;
	uint8_t rol: 1;
	uint8_t padding: 2;
	//cuerpo
	uint8_t ancho;
	uint8_t alto;
}PACKED;

typedef struct PktElemento
{
	uint8_t tipo: 6;
	uint8_t orientacion: 2;
	uint16_t posicion;
}PACKED;

typedef struct PktPosiciones
{
	uint16_t id;
	uint32_t arista: 17;
	uint8_t posicion: 6;
	uint8_t direccion: 1;
}PACKED;

typedef struct PktElementoStatus
{
	uint8_t tipo: 4;
	uint8_t orientacion: 2;
	uint8_t estado: 2;
	uint16_t posicion;
}PACKED;

typedef struct PktStart: PktCabecera
{
	uint16_t id;
}PACKED;

typedef struct PktStop: PktCabecera
{
	uint32_t puntuacion;
}PACKED;


#endif /*PAQUETES_H_*/
