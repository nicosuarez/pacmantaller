#include "Coordenada.h"


Coordenada::Coordenada():x(0),y(0),z(0) {
}


Coordenada::Coordenada(float x, float y, float z):x(x),y(y),z(z) {
}

Coordenada::Coordenada(const Coordenada &coord): x(coord.x),y(coord.y),z(coord.z) {
}

const Coordenada& Coordenada::operator= (const Coordenada &coord) {

	if (this!=&coord) {
		x=coord.x;
		y=coord.y;
		z=coord.z;
	}
	return *this;
}


Coordenada::~Coordenada() {
}


Coordenada Coordenada::operator +(const Coordenada& coord) {	

	Coordenada v;	
	v.x = x + coord.x;
	v.y = y + coord.y;
    v.z = z + coord.z;
	return v;

}



Coordenada Coordenada::operator -(const Coordenada& coord) {	

	Coordenada v;
	v.x = x - coord.x;
	v.y = y - coord.y;
    v.z = z - coord.z;
	return v;

}


Coordenada Coordenada::operator* (const float& dato) {

	Coordenada coord_aux;
	coord_aux.x = x * dato;
	coord_aux.y = y * dato;
	coord_aux.z = z * dato;	
	return coord_aux;
}
