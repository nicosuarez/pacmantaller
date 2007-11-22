///////////////////////////////////////////////////////////
//  Key.h
//  Implementation of the Class Key
//  Created on:      21-Nov-2007 23:40:19
///////////////////////////////////////////////////////////

#if !defined(EA_9FBCDE46_16D5_4a67_B181_80E0C0785BF8__INCLUDED_)
#define EA_9FBCDE46_16D5_4a67_B181_80E0C0785BF8__INCLUDED_

#include "string.h"
#include "Mensaje.h"

class Key : public Mensaje
{

public:
	Key();
	virtual ~Key();

	string Serialize();

};
#endif // !defined(EA_9FBCDE46_16D5_4a67_B181_80E0C0785BF8__INCLUDED_)
