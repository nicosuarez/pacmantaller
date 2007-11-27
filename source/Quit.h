///////////////////////////////////////////////////////////
//  Quit.h
//  Implementation of the Class Quit
//  Created on:      21-Nov-2007 23:40:21
///////////////////////////////////////////////////////////

#if !defined(EA_3528273F_A36E_4232_A4A7_4BC86A49F8F1__INCLUDED_)
#define EA_3528273F_A36E_4232_A4A7_4BC86A49F8F1__INCLUDED_

#include "string.h"
#include "Mensaje.h"

class Quit : public Mensaje
{

public:
	Quit();
	virtual ~Quit();

	char* Serialize();

};
#endif // !defined(EA_3528273F_A36E_4232_A4A7_4BC86A49F8F1__INCLUDED_)
