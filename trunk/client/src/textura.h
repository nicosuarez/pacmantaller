#ifndef TEXTURA_H
#define TEXTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/glu.h>


typedef struct {
	GLubyte  *dibujo; // Un puntero a los datos de la imagen
	GLuint	bpp;// bpp significa bits per pixel (bits por punto) es la calidad en palabras sensillas
	GLuint largo;		// Largo de la textura
	GLuint ancho;		// Ancho de la textura
	GLuint ID;		// ID de la textura, es como su nombre para opengl
} textura;

class Textura {

	public:
		int cargarTGA(char *nombre); 
		GLuint getId() {return imagen[0].ID;}

	private:
		textura	imagen[1];
};


#endif
