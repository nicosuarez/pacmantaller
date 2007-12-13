#include "Vertice.h"

Vertice::Vertice() {

	idVertice = -1;
	posMapa.x = 0;
	posMapa.y = 0;
	posMapa.z = 0;
}

Vertice::Vertice(int idVertice, Coordenada posMapa):idVertice(idVertice),posMapa(posMapa) {

}

Vertice::~Vertice() {

}

void Vertice::setCoordenada(Coordenada posMapa) {
	this->posMapa.x = posMapa.x;
	this->posMapa.y = posMapa.y;
	this->posMapa.z = posMapa.z;

} 
