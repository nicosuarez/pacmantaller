#include "Message.h"

Message::Message( std::string cadena)
{
	this->cadena = cadena;
}

Message::~Message()
{
}

int Message::getTipo()
{
	return TIPO_MESSAGE;
}

char* Message::Serialize()
{
	char* buffer = new char[ sizeof(PktCabecera) + cadena.size() ];
	PktCabecera *pkt = (PktCabecera*) buffer;
	pkt->version = 0;
	pkt->tipo = TIPO_MESSAGE;
	pkt->aux = cadena.size();
	const char *pktMensaje = buffer + sizeof(PktCabecera);
	pktMensaje = cadena.c_str();
	return buffer;
}
