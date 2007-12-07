#ifndef MUNDO_H_
#define MUNDO_H_

#include <string>
#include <queue>

using std::string;

typedef std::queue<string> tQueueNiveles;

class Mundo
{
private:
	tQueueNiveles niveles;
	
public:
	Mundo();
	//Cola de niveles cada nivel tiene el path del mapa asociado.
	tQueueNiveles* getNiveles();
};

#endif /*MUNDO_H_*/
