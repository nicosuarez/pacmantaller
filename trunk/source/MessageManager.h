///////////////////////////////////////////////////////////
//  MessageManager.h
//  Implementation of the Class MessageManager
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#if !defined(EA_57ABE731_4292_4e06_AFCC_C8A3662E7849__INCLUDED_)
#define EA_57ABE731_4292_4e06_AFCC_C8A3662E7849__INCLUDED_

#include "ParseMessage.h"
#include <queue>

class MessageManager
{

public:
	MessageManager();
	virtual ~MessageManager();
	ParseMessage *m_ParseMessage;

	void main();
	void procesarMensaje();

private:
	std::queue<Mensaje*> mensajes;

};
#endif // !defined(EA_57ABE731_4292_4e06_AFCC_C8A3662E7849__INCLUDED_)
