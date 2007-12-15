#ifndef MODEL_H_
#define MODEL_H_

#include <GL/glut.h>
#include "Coordenada.h"


struct Triangle {
	unsigned int p0, uv0, n0;
	unsigned int p1, uv1, n1;
	unsigned int p2, uv2, n2; 
};

struct UV {
	float u;
	float v;
};


class Texture {
	public:
		Texture();
		~Texture();
	
		unsigned int id;
	
		GLubyte *data;
		GLint width;
		GLint height;
	
		GLint size;
		bool repT;
		bool repS;
};


struct Material {
	GLfloat amb[4];
	GLfloat dif[4];
	GLfloat spe[4];
	GLfloat shininess;
	Material() {
		amb[0] = amb[1] = amb[2] = amb[3] = 1.0f;
		dif[0] = dif[1] = dif[2] = dif[3] = 1.0f;
		spe[0] = spe[1] = spe[2] = spe[3] = 1.0f;
		shininess = 0.0f;
	}
};


class Model {

	public:
		Model();
		~Model();

		Coordenada *Points;
		UV *UVs;
		Coordenada *Normals;
		Triangle *Tris;
			
		unsigned indSize;
		unsigned uvSize;
		unsigned norSize;
		unsigned triSize;
	
		Texture  *tex;
		Material *mat;
	
		Coordenada  BBox;
		Coordenada  Center;	

};

#endif /*MODEL_H_*/
