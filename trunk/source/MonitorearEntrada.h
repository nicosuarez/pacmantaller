#ifndef MONITOREARENTRADA_H_
#define MONITOREARENTRADA_H_

#include "Thread.h"
#include <iostream>
#include <string>

typedef bool* pBool;

using std::string;
using std::cin;

class MonitorearEntrada : public Thread
{
private:
	pBool cerrarServidor;
public:
	MonitorearEntrada(pBool cerrarServidor);
	void main();
};

#endif /*MONITOREARENTRADA_H_*/
