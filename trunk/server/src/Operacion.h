///////////////////////////////////////////////////////////
//  Operacion.h
//  Implementation of the Class Operacion
//  Created on:      21-Nov-2007 23:40:20
///////////////////////////////////////////////////////////

#if !defined(EA_9A3DFB1D_40D2_4167_894A_F5464BCE129F__INCLUDED_)
#define EA_9A3DFB1D_40D2_4167_894A_F5464BCE129F__INCLUDED_
/**
 * Clase Abstracta que permite implementar mediante el polimorfismo ejecutar cada
 * operacion hija.
 */
class Operacion
{

public:
	Operacion();
	
	virtual ~Operacion();
	
	 // Valida y aplica la operacion* retorna TRUE(exito),FALSE(error)
	virtual bool ejecutar()=0;

protected:
	virtual void internalProcess();
	virtual bool validarOperacion();

};
#endif // !defined(EA_9A3DFB1D_40D2_4167_894A_F5464BCE129F__INCLUDED_)
