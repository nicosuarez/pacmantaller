///////////////////////////////////////////////////////////
//  Key.h
//  Implementation of the Class Key
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_9FBCDE46_16D5_4a67_B181_80E0C0785BF8__INCLUDED_)
#define EA_9FBCDE46_16D5_4a67_B181_80E0C0785BF8__INCLUDED_

#include "Mensaje.h"
#define TIPO_KEY 5

class Key : public Mensaje
{
	int key;

public:
	Key( int key );
	
	virtual ~Key();
	
	int getTipo();

	char* Serialize();

};
#endif // !defined(EA_9FBCDE46_16D5_4a67_B181_80E0C0785BF8__INCLUDED_)
