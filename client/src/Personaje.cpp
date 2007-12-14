///////////////////////////////////////////////////////////
//  Personaje.cpp
//  Implementation of the Class Personaje
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#include "Personaje.h"


Personaje::Personaje(){

}

Personaje::Personaje(Posicion& posicion){
	this->posicion=posicion;
}

Personaje::Personaje(Posicion& posicion, Coordenada cTranslate):posicion(posicion),
cTranslate(cTranslate),model(NULL) {

	/*cTranslate = Coordenada(0.0f, 0.0f, 0.0f);
	cRotate = Coordenada(0.0f, 0.0f, 0.0f);
	cScale = Coordenada(1.0f, 1.0f, 1.0f);*/
}

Personaje::~Personaje(){

}



/**
 * Posicion del personaje en el mapa
 */
Posicion* Personaje::GetPosicion(){

	return &posicion;
}


/**
 * Velocidad del personaje
 */
int Personaje::GetVelocidad(){

	return velocidad;
}

/**
 * Retorna el Identificador de personaje
 */
int Personaje::GetId()const
{
	return idPersonaje;
}


/**
 * Identificador de personaje
 */
void Personaje::SetId(int id){

	idPersonaje = id;
}


/**
 * Posicion del personaje en el mapa
 */
void Personaje::SetPosicion(Posicion newVal){

	posicion.setArista( newVal.getArista() );
	posicion.setPosicionArista( newVal.getPosicionArista() );
	posicion.setDireccion( newVal.getDireccion() );
}


/**
 * Velocidad del personaje
 */
void Personaje::SetVelocidad(int newVal){

	velocidad = newVal;
}


void Personaje::renderizar() {
	
	glPushMatrix();
	
	glTranslatef(cTranslate.x, cTranslate.y, cTranslate.z);//(0,0,0) para el escenario 
/*	glRotatef(cRotate.y, 0.0f, 1.0f, 0.0f);
	glRotatef(cRotate.x, 1.0f, 0.0f, 0.0f);
	glRotatef(cRotate.z, 0.0f, 0.0f, 1.0f);
	glScalef(cScale.x, cScale.y, cScale.z);*/
	
	if (model != NULL) {

		if (model->tex != NULL) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture (GL_TEXTURE_2D, model->tex->id);
		} else {
			glDisable(GL_TEXTURE_2D);
		}

		if (model->mat != NULL) {
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glMaterialfv(GL_FRONT, GL_AMBIENT, model->mat->amb);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, model->mat->dif);
			glMaterialfv(GL_FRONT, GL_SPECULAR, model->mat->spe);
			glMaterialf(GL_FRONT, GL_SHININESS, model->mat->shininess);
		} else {
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);			
		}

		for (unsigned int i = 0; i < model->triSize; i++) {
			Coordenada p, n;
			glBegin(GL_TRIANGLES);
				UV uv;

				p = model->Points[model->Tris[i].p0-1];
				n = model->Normals[model->Tris[i].n0-1];
				uv = model->UVs[model->Tris[i].uv0-1];

				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glNormal3f(n.x, n.y, n.z);
				glTexCoord2f(uv.u, uv.v);
				glVertex3f(p.x, p.y, p.z);

				p = model->Points[model->Tris[i].p1-1];
				n = model->Normals[model->Tris[i].n1-1];
				uv = model->UVs[model->Tris[i].uv1-1];

				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glNormal3f(n.x, n.y, n.z);
				glTexCoord2f(uv.u, uv.v);
				glVertex3f(p.x, p.y, p.z);

				p = model->Points[model->Tris[i].p2-1];
				n = model->Normals[model->Tris[i].n2-1];
				uv = model->UVs[model->Tris[i].uv2-1];

				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				glNormal3f(n.x, n.y, n.z);
				glTexCoord2f(uv.u, uv.v);
				glVertex3f(p.x, p.y, p.z);
			glEnd();
		}
	}

	glPopMatrix();
}
