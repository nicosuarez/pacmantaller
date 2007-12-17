#ifndef CORDENADA_H_
#define CORDENADA_H_

#include <iostream>

class Cordenada
{
	private:
		int fila;
		int columna;
	public:
		Cordenada(int parFila,int parColumna);
		Cordenada(){}
		Cordenada(const Cordenada& C);
		bool operator==(const Cordenada &C) const;
		bool operator<(const Cordenada &C) const;
		Cordenada& operator=(const Cordenada &C);
		void set(int parFila,int parColumna);
		void get(int &parFila,int &parColumna);		
};

#endif /*CORDENADA_H_*/
