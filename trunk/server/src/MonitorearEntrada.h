#ifndef MONITOREARENTRADA_H_
#define MONITOREARENTRADA_H_

#include "Thread.h"
#include "CerrarServidorOp.h"
#include <iostream>
#include <string>
#include "LogResource.h"

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
