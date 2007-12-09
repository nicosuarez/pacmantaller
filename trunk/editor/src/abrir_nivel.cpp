#include "abrir_nivel.h"

AbrirNivel::AbrirNivel(Glib::RefPtr<Gnome::Glade::Xml> &parRefXml):nroSel(-1),refXml(parRefXml),presCancelar(false)
{
	refXml -> get_widget("dialogoAbrir",pDialogoAbrir);
	refXml -> get_widget("comboAbrir",pComboAbrir);
	refXml -> get_widget("botonCancelarAbrir",pBotonCancelarAbrir);
	
	pBotonCancelarAbrir -> signal_clicked().connect( sigc::mem_fun(*this,&AbrirNivel::funcBotonCancelar) ); 
}

void AbrirNivel::correr(int nroMaximo)
{
	//Le pone los numeros al combo hasta el nro de nivel maximo
	std::list<Glib::ustring> listaNumeros;
	
	if  (nroMaximo >= 0)
		for (int nro = 0 ; nro <= nroMaximo ; nro += 1)
		{
			std::ostringstream caja;
			caja << nro;
			listaNumeros.push_back(caja.str());
		}
		
	pComboAbrir -> set_popdown_strings(listaNumeros);
	
	//Pongo a correr el dialogo
	pDialogoAbrir -> run();
	pDialogoAbrir -> hide();
}

void AbrirNivel::funcBotonCancelar()
{
	presCancelar = true;	
}

int AbrirNivel::getNroSel()
{
	if (!presCancelar) //Si no se presiono cancelar
	{
		Gtk::Entry *pEntrada = pComboAbrir -> get_entry();
		if (pEntrada)
		{
			std::istringstream caja( pEntrada -> get_text() );
			caja >> nroSel;
		}
		return nroSel;
	}
	else
		presCancelar = false; //Vuelvo al estado original
	return NINGUNO;
}
