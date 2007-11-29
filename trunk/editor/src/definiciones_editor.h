#ifndef definiciones_editor_h
#define definiciones_editor_h

//Maxima cantidad de Filas y Columnas

#define MAX_CANT_FILAS                  20
#define MAX_CANT_COLUMNAS               20

//Path de imagenes
#define PATH_BLANCO                     "/home/maxi/Editor de Mundos/Imagenes/Blanco.jpg"
#define PATH_IMG1                       "/home/maxi/Editor de Mundos/Imagenes/forma1.jpg"
#define PATH_IMG2                       "/home/maxi/Editor de Mundos/Imagenes/forma2.jpg"
#define PATH_IMG3                       "/home/maxi/Editor de Mundos/Imagenes/forma3.jpg"
#define PATH_IMG4                       "/home/maxi/Editor de Mundos/Imagenes/forma4.jpg"
#define PATH_IMG5                       "/home/maxi/Editor de Mundos/Imagenes/forma5.jpg"
#define PATH_IMG6                       "/home/maxi/Editor de Mundos/Imagenes/forma6.jpg"
#define PATH_IMG7                       "/home/maxi/Editor de Mundos/Imagenes/forma7.jpg"
#define PATH_IMG8                       "/home/maxi/Editor de Mundos/Imagenes/forma8.jpg"
#define PATH_IMG9                       "/home/maxi/Editor de Mundos/Imagenes/forma9.jpg"
#define PATH_IMG1_SEL                   "/home/maxi/Editor de Mundos/Imagenes/forma1_Sel.jpg"
#define PATH_IMG2_SEL                   "/home/maxi/Editor de Mundos/Imagenes/forma2_Sel.jpg"
#define PATH_IMG3_SEL                   "/home/maxi/Editor de Mundos/Imagenes/forma3_Sel.jpg"
#define PATH_IMG4_SEL                   "/home/maxi/Editor de Mundos/Imagenes/forma4_Sel.jpg"
#define PATH_IMG5_SEL                   "/home/maxi/Editor de Mundos/Imagenes/forma5_Sel.jpg"
#define PATH_IMG6_SEL                   "/home/maxi/Editor de Mundos/Imagenes/forma6_Sel.jpg"
#define PATH_IMG7_SEL                   "/home/maxi/Editor de Mundos/Imagenes/forma7_Sel.jpg"
#define PATH_IMG8_SEL                   "/home/maxi/Editor de Mundos/Imagenes/forma8_Sel.jpg"
#define PATH_IMG9_SEL                   "/home/maxi/Editor de Mundos/Imagenes/forma9_Sel.jpg"
#define PATH_PUNTO_H                    "/home/maxi/Editor de Mundos/Imagenes/puntoH.jpg"
#define PATH_PUNTO_V                    "/home/maxi/Editor de Mundos/Imagenes/puntoV.jpg"
#define PATH_PUNTO_C                    "/home/maxi/Editor de Mundos/Imagenes/puntoC.jpg"
#define PATH_PUNTO_V2                   "/home/maxi/Editor de Mundos/Imagenes/puntoV2.jpg"
#define PATH_PUNTO_N                    "/home/maxi/Editor de Mundos/Imagenes/puntoN.jpg"
#define PATH_PUNTO_F                    "/home/maxi/Editor de Mundos/Imagenes/puntoF.jpg"
#define PATH_PUNTO_F2                   "/home/maxi/Editor de Mundos/Imagenes/puntoF2.jpg"
#define PATH_PUNTO_F3                   "/home/maxi/Editor de Mundos/Imagenes/puntoF3.jpg"
#define PATH_PUNTO_F4                   "/home/maxi/Editor de Mundos/Imagenes/puntoF4.jpg"
#define PATH_PUNTO_BONUS                "/home/maxi/Editor de Mundos/Imagenes/puntoBonus.jpg"
#define PATH_PUNTO_P                    "/home/maxi/Editor de Mundos/Imagenes/puntoP.jpg"
#define PATH_PUNTO_POW                  "/home/maxi/Editor de Mundos/Imagenes/puntoPow.jpg"
#define PATH_NEGRO                      "/home/maxi/Editor de Mundos/Imagenes/Negro.jpg"
#define PATH_PUNTO_H2                   "/home/maxi/Editor de Mundos/Imagenes/puntoH2.jpg"
#define PATH_PUNTO_H2b                  "/home/maxi/Editor de Mundos/Imagenes/puntoH2b.jpg"
#define PATH_PUNTO_V2b                  "/home/maxi/Editor de Mundos/Imagenes/puntoV2b.jpg"
//Paths de la casa de los fantasmas
#define PATH_PUNTO_C1                   "/home/maxi/Editor de Mundos/Imagenes/PuntoC1.jpg"
#define PATH_PUNTO_CL                   "/home/maxi/Editor de Mundos/Imagenes/PuntoCI.jpg"
#define PATH_PUNTO_C2                   "/home/maxi/Editor de Mundos/Imagenes/PuntoC2.jpg"
#define PATH_PUNTO_C3                   "/home/maxi/Editor de Mundos/Imagenes/PuntoC3.jpg"
#define PATH_PUNTO_C4                   "/home/maxi/Editor de Mundos/Imagenes/PuntoC4.jpg"
#define PATH_PUNTO_CN                   "/home/maxi/Editor de Mundos/Imagenes/puntoCN.jpg"
#define PATH_PUNTO_C5                   "/home/maxi/Editor de Mundos/Imagenes/PuntoC5.jpg"
#define PATH_PUNTO_C5b                  "/home/maxi/Editor de Mundos/Imagenes/PuntoC5b.jpg"
#define PATH_PUNTO_CIb                  "/home/maxi/Editor de Mundos/Imagenes/PuntoCIb.jpg"
#define PATH_PUNTO_C5c                  "/home/maxi/Editor de Mundos/Imagenes/PuntoC5c.jpg"
#define PATH_PUNTO_CIc                  "/home/maxi/Editor de Mundos/Imagenes/PuntoCIc.jpg"
#define PATH_PUNTO_C5d                  "/home/maxi/Editor de Mundos/Imagenes/PuntoC5d.jpg"
#define PATH_PUNTO_CId                  "/home/maxi/Editor de Mundos/Imagenes/PuntoCId.jpg"
#define PATH_PUNTO_CR1                  "/home/maxi/Editor de Mundos/Imagenes/puntoCR1.jpg"
#define PATH_PUNTO_CR2                  "/home/maxi/Editor de Mundos/Imagenes/puntoCR2.jpg"
#define PATH_PUNTO_CR3                  "/home/maxi/Editor de Mundos/Imagenes/puntoCR3.jpg"

#define CANT_IMAGENES                   9

//Tipo de Datos de InsertarImag
typedef enum {MARCAR,LIMPIAR,INSERTAR} TipoOperacion;
//Tipo de Datos del editor
typedef enum {NADA,MODO_INSERTAR,MODO_ELIMINAR} TipoModo;

#endif
