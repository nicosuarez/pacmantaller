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


Personaje::~Personaje() {

}


/**
 * Posicion del personaje en el mapa
 */
Posicion* Personaje::GetPosicion() {

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
void Personaje::SetPosicion(Posicion pos){

	posicion.setArista( pos.getArista() );
	posicion.setPosicionArista( pos.getPosicionArista() );
	posicion.setDireccion( pos.getDireccion() );
}


/**
 * Velocidad del personaje
 */
void Personaje::SetVelocidad(int newVal){

	velocidad = newVal;
}

void Personaje::SetModel(Model* model){
	this->model=model;
}

void Personaje::SetRotacion(Coordenada rotacion) { 
	
	this->rotacion = rotacion;
}

void Personaje::SetCoord(Coordenada coord) { 
	
	this->coord= coord;
}


void Personaje::renderizar() {
	
	glPushMatrix();
	
	glTranslatef(coord.x, coord.y, coord.z);//(0,0,0) para el escenario 
	glRotatef(rotacion.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rotacion.y, 0.0f, 1.0f, 0.0f);	
	glRotatef(rotacion.z, 0.0f, 0.0f, 1.0f);
	if (GetRol()==0)
		glScalef(P_ESCALAX, P_ESCALAY, P_ESCALAZ);		
	else 
		glScalef(F_ESCALAX, F_ESCALAY, F_ESCALAZ);
	
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
