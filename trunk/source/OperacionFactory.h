///////////////////////////////////////////////////////////
//  OperacionFactory.h
//  Implementation of the Class OperacionFactory
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#if !defined(EA_7CF8D591_8247_4d9b_9565_5EFEFD4B5972__INCLUDED_)
#define EA_7CF8D591_8247_4d9b_9565_5EFEFD4B5972__INCLUDED_

/**
 * Fabrica de operaciones, dado el codigo de operacion se instancia una
 * operacion del tipo correspondiente.
 */
class OperacionFactory
{

public:
	OperacionFactory();
	virtual ~OperacionFactory();

	void construir(bool opC);

};
#endif // !defined(EA_7CF8D591_8247_4d9b_9565_5EFEFD4B5972__INCLUDED_)
