#include "cordenada.h"

Cordenada::Cordenada(int parFila,int parColumna):fila(parFila),columna(parColumna)
{
}

Cordenada::Cordenada(const Cordenada& C)
{
	fila = C.fila;
	columna = C.columna;
}

bool Cordenada::operator==(const Cordenada &C) const 
{ 
	return ( (fila == C.fila) && (columna == C.columna) ); 
}

bool Cordenada::operator<(const Cordenada &C) const
{
	if (fila < C.fila)
		return true;
	if (fila == C.fila)
		return ( (columna < C.columna) );
	return false;
}

Cordenada& Cordenada::operator=(const Cordenada &C)
{
	fila = C.fila;
	columna = C.columna;
	return(*this);
}

void Cordenada::set(int parFila,int parColumna)
{
	fila = parFila;
	columna = parColumna;
}
