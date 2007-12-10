///////////////////////////////////////////////////////////
//  Key.h
//  Implementation of the Class Key
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_9FBCDE46_16D5_4a67_B181_80E0C0785BF8__INCLUDED_)
#define EA_9FBCDE46_16D5_4a67_B181_80E0C0785BF8__INCLUDED_

#include "Mensaje.h"

#define NONE -1
#define KEY_ARRIBA 0
#define KEY_ABAJO 1
#define KEY_IZQUIERDA 2
#define KEY_DERECHA 3
#define KEY_ESCAPE 4

class Key : public Mensaje
{
	int key;

public:
	
	static const int KEY_TYPE = 5;
	
	Key( int key );
	
	virtual ~Key();

	char* Serialize();

};
#endif // !defined(EA_9FBCDE46_16D5_4a67_B181_80E0C0785BF8__INCLUDED_)
