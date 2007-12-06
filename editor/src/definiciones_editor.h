#ifndef definiciones_editor_h
#define definiciones_editor_h

//Maxima cantidad de Filas y Columnas

#define MAX_CANT_FILAS                  20
#define MAX_CANT_COLUMNAS               20

//Path de imagenes
#define PATH_BLANCO                     "Imagenes/Blanco.jpg"
#define PATH_IMG1                       "Imagenes/forma1.jpg"
#define PATH_IMG2                       "Imagenes/forma2.jpg"
#define PATH_IMG3                       "Imagenes/forma3.jpg"
#define PATH_IMG4                       "Imagenes/forma4.jpg"
#define PATH_IMG5                       "Imagenes/forma5.jpg"
#define PATH_IMG6                       "Imagenes/forma6.jpg"
#define PATH_IMG7                       "Imagenes/forma7.jpg"
#define PATH_IMG8                       "Imagenes/forma8.jpg"
#define PATH_IMG9                       "Imagenes/forma9.jpg"
#define PATH_IMG1_SEL                   "Imagenes/forma1_Sel.jpg"
#define PATH_IMG2_SEL                   "Imagenes/forma2_Sel.jpg"
#define PATH_IMG3_SEL                   "Imagenes/forma3_Sel.jpg"
#define PATH_IMG4_SEL                   "Imagenes/forma4_Sel.jpg"
#define PATH_IMG5_SEL                   "Imagenes/forma5_Sel.jpg"
#define PATH_IMG6_SEL                   "Imagenes/forma6_Sel.jpg"
#define PATH_IMG7_SEL                   "Imagenes/forma7_Sel.jpg"
#define PATH_IMG8_SEL                   "Imagenes/forma8_Sel.jpg"
#define PATH_IMG9_SEL                   "Imagenes/forma9_Sel.jpg"
#define PATH_PUNTO_H                    "Imagenes/puntoH.jpg"
#define PATH_PUNTO_V                    "Imagenes/puntoV.jpg"
#define PATH_PUNTO_C                    "Imagenes/puntoC.jpg"
#define PATH_PUNTO_V2                   "Imagenes/puntoV2.jpg"
#define PATH_PUNTO_N                    "Imagenes/puntoN.jpg"
#define PATH_PUNTO_F                    "Imagenes/puntoF.jpg"
#define PATH_PUNTO_F2                   "Imagenes/puntoF2.jpg"
#define PATH_PUNTO_F3                   "Imagenes/puntoF3.jpg"
#define PATH_PUNTO_F4                   "Imagenes/puntoF4.jpg"
#define PATH_PUNTO_BONUS                "Imagenes/puntoBonus.jpg"
#define PATH_PUNTO_P                    "Imagenes/puntoP.jpg"
#define PATH_PUNTO_POW                  "Imagenes/puntoPow.jpg"
#define PATH_NEGRO                      "Imagenes/Negro.jpg"
#define PATH_PUNTO_H2                   "Imagenes/puntoH2.jpg"
#define PATH_PUNTO_H2b                  "Imagenes/puntoH2b.jpg"
#define PATH_PUNTO_V2b                  "Imagenes/puntoV2b.jpg"
//Paths de la casa de los fantasmas
#define PATH_PUNTO_C1                   "Imagenes/PuntoC1.jpg"
#define PATH_PUNTO_CL                   "Imagenes/PuntoCI.jpg"
#define PATH_PUNTO_C2                   "Imagenes/PuntoC2.jpg"
#define PATH_PUNTO_C3                   "Imagenes/PuntoC3.jpg"
#define PATH_PUNTO_C4                   "Imagenes/PuntoC4.jpg"
#define PATH_PUNTO_CN                   "Imagenes/puntoCN.jpg"
#define PATH_PUNTO_C5                   "Imagenes/PuntoC5.jpg"
#define PATH_PUNTO_C5b                  "Imagenes/PuntoC5b.jpg"
#define PATH_PUNTO_CIb                  "Imagenes/PuntoCIb.jpg"
#define PATH_PUNTO_C5c                  "Imagenes/PuntoC5c.jpg"
#define PATH_PUNTO_CIc                  "Imagenes/PuntoCIc.jpg"
#define PATH_PUNTO_C5d                  "Imagenes/PuntoC5d.jpg"
#define PATH_PUNTO_CId                  "Imagenes/PuntoCId.jpg"
#define PATH_PUNTO_CR1                  "Imagenes/puntoCR1.jpg"
#define PATH_PUNTO_CR2                  "Imagenes/puntoCR2.jpg"
#define PATH_PUNTO_CR3                  "Imagenes/puntoCR3.jpg"

#define CANT_IMAGENES                   9

//Tipo de Datos de InsertarImag
typedef enum {MARCAR,LIMPIAR,INSERTAR} TipoOperacion;
//Tipo de Datos del editor
typedef enum {NADA,MODO_INSERTAR,MODO_ELIMINAR} TipoModo;

#endif
