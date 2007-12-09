#ifndef DEFINICIONES_EDITOR_H_
#define DEFINICIONES_EDITOR_H_

//Maxima cantidad de Filas y Columnas

#define MAX_CANT_FILAS                  20
#define MAX_CANT_COLUMNAS               20

//Path de imagenes
#define PATH_BLANCO                     "Archivos_Editor/Imagenes/Blanco.jpg"
#define PATH_IMG1                       "Archivos_Editor/Imagenes/forma1.jpg"
#define PATH_IMG2                       "Archivos_Editor/Imagenes/forma2.jpg"
#define PATH_IMG3                       "Archivos_Editor/Imagenes/forma3.jpg"
#define PATH_IMG4                       "Archivos_Editor/Imagenes/forma4.jpg"
#define PATH_IMG5                       "Archivos_Editor/Imagenes/forma5.jpg"
#define PATH_IMG6                       "Archivos_Editor/Imagenes/forma6.jpg"
#define PATH_IMG7                       "Archivos_Editor/Imagenes/forma7.jpg"
#define PATH_IMG8                       "Archivos_Editor/Imagenes/forma8.jpg"
#define PATH_IMG9                       "Archivos_Editor/Imagenes/forma9.jpg"
#define PATH_IMG1_SEL                   "Archivos_Editor/Imagenes/forma1_Sel.jpg"
#define PATH_IMG2_SEL                   "Archivos_Editor/Imagenes/forma2_Sel.jpg"
#define PATH_IMG3_SEL                   "Archivos_Editor/Imagenes/forma3_Sel.jpg"
#define PATH_IMG4_SEL                   "Archivos_Editor/Imagenes/forma4_Sel.jpg"
#define PATH_IMG5_SEL                   "Archivos_Editor/Imagenes/forma5_Sel.jpg"
#define PATH_IMG6_SEL                   "Archivos_Editor/Imagenes/forma6_Sel.jpg"
#define PATH_IMG7_SEL                   "Archivos_Editor/Imagenes/forma7_Sel.jpg"
#define PATH_IMG8_SEL                   "Archivos_Editor/Imagenes/forma8_Sel.jpg"
#define PATH_IMG9_SEL                   "Archivos_Editor/Imagenes/forma9_Sel.jpg"
#define PATH_PUNTO_H                    "Archivos_Editor/Imagenes/puntoH.jpg"
#define PATH_PUNTO_V                    "Archivos_Editor/Imagenes/puntoV.jpg"
#define PATH_PUNTO_C                    "Archivos_Editor/Imagenes/puntoC.jpg"
#define PATH_PUNTO_V2                   "Archivos_Editor/Imagenes/puntoV2.jpg"
#define PATH_PUNTO_N                    "Archivos_Editor/Imagenes/puntoN.jpg"
#define PATH_PUNTO_F                    "Archivos_Editor/Imagenes/puntoF.jpg"
#define PATH_PUNTO_F2                   "Archivos_Editor/Imagenes/puntoF2.jpg"
#define PATH_PUNTO_F3                   "Archivos_Editor/Imagenes/puntoF3.jpg"
#define PATH_PUNTO_F4                   "Archivos_Editor/Imagenes/puntoF4.jpg"
#define PATH_PUNTO_BONUS                "Archivos_Editor/Imagenes/puntoBonus.jpg"
#define PATH_PUNTO_P                    "Archivos_Editor/Imagenes/puntoP.jpg"
#define PATH_PUNTO_POW                  "Archivos_Editor/Imagenes/puntoPow.jpg"
#define PATH_NEGRO                      "Archivos_Editor/Imagenes/Negro.jpg"
#define PATH_PUNTO_H2                   "Archivos_Editor/Imagenes/puntoH2.jpg"
#define PATH_PUNTO_H2b                  "Archivos_Editor/Imagenes/puntoH2b.jpg"
#define PATH_PUNTO_V2b                  "Archivos_Editor/Imagenes/puntoV2b.jpg"
//Paths de la casa de los fantasmas
#define PATH_PUNTO_C1                   "Archivos_Editor/Imagenes/PuntoC1.jpg"
#define PATH_PUNTO_CL                   "Archivos_Editor/Imagenes/PuntoCI.jpg"
#define PATH_PUNTO_C2                   "Archivos_Editor/Imagenes/PuntoC2.jpg"
#define PATH_PUNTO_C3                   "Archivos_Editor/Imagenes/PuntoC3.jpg"
#define PATH_PUNTO_C4                   "Archivos_Editor/Imagenes/PuntoC4.jpg"
#define PATH_PUNTO_CN                   "Archivos_Editor/Imagenes/puntoCN.jpg"
#define PATH_PUNTO_C5                   "Archivos_Editor/Imagenes/PuntoC5.jpg"
#define PATH_PUNTO_C5b                  "Archivos_Editor/Imagenes/PuntoC5b.jpg"
#define PATH_PUNTO_CIb                  "Archivos_Editor/Imagenes/PuntoCIb.jpg"
#define PATH_PUNTO_C5c                  "Archivos_Editor/Imagenes/PuntoC5c.jpg"
#define PATH_PUNTO_CIc                  "Archivos_Editor/Imagenes/PuntoCIc.jpg"
#define PATH_PUNTO_C5d                  "Archivos_Editor/Imagenes/PuntoC5d.jpg"
#define PATH_PUNTO_CId                  "Archivos_Editor/Imagenes/PuntoCId.jpg"
#define PATH_PUNTO_CR1                  "Archivos_Editor/Imagenes/puntoCR1.jpg"
#define PATH_PUNTO_CR2                  "Archivos_Editor/Imagenes/puntoCR2.jpg"
#define PATH_PUNTO_CR3                  "Archivos_Editor/Imagenes/puntoCR3.jpg"

#define CANT_IMAGENES                   9

//Tipo de Datos de InsertarImag
typedef enum {MARCAR,LIMPIAR,INSERTAR} TipoOperacion;
//Tipo de Datos del editor
typedef enum {NADA,MODO_INSERTAR,MODO_ELIMINAR} TipoModo;

//Defines de exito y error
#define EXITO                           0
#define ERROR                          -1

//Defines para el Parser
#define PATH_NIVELES                    "../server/maps/Mundo.xml"
#define PATH_MAPA                       "../server/maps/Mapa"
#define PATH_CONFIGURACION              "Archivos_Editor/Configuracion.xml"
#define PATH_MAPA_EDITOR                "Archivos_Editor/MapaEditor"

//Defines para el Abrir_Nivel
#define NINGUNO                         -1

#endif /*DEFINICIONES_EDITOR_H_*/
