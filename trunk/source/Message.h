#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Mensaje.h"
#include <string>
#define TIPO_MESSAGE 6

class Message : public Mensaje
{
	std::string cadena;
public:
	Message( std::string cadena );
	
	virtual ~Message();
	
	int getTipo();

	char* Serialize();
};

#endif /*MESSAGE_H_*/
