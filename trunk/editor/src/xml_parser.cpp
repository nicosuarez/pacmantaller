#include "xml_parser.h"

void XmlParser::armarArchivoNiveles(int nroNivel)
{
	//Armo el archivo de niveles	
	if (getProximoNivel() == nroNivel) //Se agrego un nuevo nivel
	{
		xmlpp::Document documento;
		xmlpp::Element* nodoRaiz = documento.create_root_node("Mundo");
		for (int i = 0 ; i <= nroNivel ; i++)
		{
			xmlpp::Element* nodoHijo = nodoRaiz->add_child("Mapa");
			std::string ruta = PATH_MAPA;
			std::ostringstream caja;
			caja << i;
			ruta += caja.str();
			ruta += ".xml";
			nodoHijo->set_attribute("Path",ruta);
		}
	
		//Volcamos todo al archivo
		Glib::ustring cadena = documento.write_to_string();
		std::ofstream archivo(PATH_NIVELES);
		archivo << cadena;
		archivo.close();
	}
}

std::string XmlParser::obtenerOrientacion(int a,int cantFilas,int cantColumnas)
{
	int id;
	
	for ( int f = 0 ; f < cantFilas ; f++ )
		for ( int c = 0 ; c < cantColumnas ; c++ )
		{
			id = f*cantFilas + c;
			if ( (id + f*cantColumnas) == a)
				return ("NORTE");
			if ( ( (id + f*cantColumnas) +cantColumnas) == a)
				return ("ESTE"); 
		}  
	return ("ESTE");//NO deberia llegar aca
}

void XmlParser::armarArchivoMapa(int nroNivel,int alto,int ancho,Grafo &G,std::list<RegElemento>& listaMod,std::list<Cordenada> listaVerticesCasa,std::string orientacion)
{
	xmlpp::Document documento;
	xmlpp::Element* nodoRaiz = documento.create_root_node("Mapa");
	std::ostringstream cajaAlto,cajaAncho,cajaNro;

	nodoRaiz -> add_child_comment("\n"); //Agrego enter
	
	//Ancho y alto
	xmlpp::Element* nodoHijoAncho = nodoRaiz->add_child("Ancho");
	nodoRaiz -> add_child_comment("\n"); //Agrego enter
	xmlpp::Element* nodoHijoAlto = nodoRaiz->add_child("Alto");
	nodoRaiz -> add_child_comment("\n"); //Agrego enter
	cajaAlto << alto;
	nodoHijoAlto -> set_attribute("valor",cajaAlto.str());
	cajaAncho << ancho;
	nodoHijoAncho->set_attribute("valor",cajaAncho.str());
	
	//Grafo
	xmlpp::Element* nodoHijoGrafo = nodoRaiz->add_child("Grafo");
	nodoHijoGrafo -> add_child_comment("\n"); //Agrego enter
	std::list<RegArista> listaDeAristas = G.getListaDeAristas();
	for (std::list<RegArista>::iterator it = listaDeAristas.begin() ; it != listaDeAristas.end() ; it++ )
	{
		int a,v1,v2;
		it -> get(a,v1,v2);
		std::string orientacion  = obtenerOrientacion(a,alto,ancho);
		xmlpp::Element* nodoHijoArista = nodoHijoGrafo->add_child("Arista");
		std::ostringstream cajaA,cajaV1,cajaV2;
		cajaA << a;
		cajaV1 << v1;
		cajaV2 << v2;
		nodoHijoArista -> set_attribute("id",cajaA.str());
		nodoHijoArista -> set_attribute("orientacion",orientacion.c_str());
		xmlpp::Element* nodoHijoVertice1 = nodoHijoArista->add_child("Vertice");	
		nodoHijoVertice1 -> set_attribute("id",cajaV1.str());
		xmlpp::Element* nodoHijoVertice2 = nodoHijoArista->add_child("Vertice");	
		nodoHijoVertice2 -> set_attribute("id",cajaV2.str());
		nodoHijoGrafo -> add_child_comment("\n"); //Agrego enter
	}
	nodoRaiz -> add_child_comment("\n"); //Agrego enter
	//Elementos
	xmlpp::Element* nodoHijoElementos = nodoRaiz->add_child("Elementos");
	nodoHijoElementos -> add_child_comment("\n"); //Agrego enter
	for (std::list<RegElemento>::iterator it = listaMod.begin() ; it != listaMod.end() ; it++ )
	{
		int nroMod,rot,f,c,idV;
		std::ostringstream caja;
		std::string tipo;
		
		xmlpp::Element* nodoHijoElemento = nodoHijoElementos->add_child("Elemento");
		it -> get(nroMod,rot,f,c);
		if (nroMod == 6)
			tipo = "PacMan";
		if (nroMod == 7)
			tipo = "PowerUp";
		if (nroMod == 8)
			tipo = "Bonus";	
		nodoHijoElemento -> set_attribute("tipo",tipo.c_str());
		idV = f * ancho + c;
		caja << idV;
		nodoHijoElemento -> set_attribute("idv",caja.str());
		nodoHijoElementos -> add_child_comment("\n"); //Agrego enter
	}
	
	//Casa de los fantasmas
	xmlpp::Element* nodoHijoCasa = nodoHijoElementos->add_child("Elemento");
	nodoHijoCasa -> set_attribute("tipo","CasaFantasmas");
	int i = 0;
	for (std::list<Cordenada>::iterator it = listaVerticesCasa.begin() ; it != listaVerticesCasa.end() ; it++)
	{
		int f,c,idV;
		std::ostringstream caja,cajaN;
		
		it -> get(f,c);
		idV = f*ancho + c;
		caja << idV;
		cajaN << i;
		nodoHijoCasa -> set_attribute("idv"+cajaN.str(),caja.str());
		i++;
	}
	nodoHijoCasa -> set_attribute("orientacion",orientacion.c_str());
	//Se graba en el archivo
	Glib::ustring cadena = documento.write_to_string();
	std::string nombre = PATH_MAPA;
	cajaNro << nroNivel;
	nombre += cajaNro.str();
	nombre += ".xml";
	std::ofstream archivo(nombre.c_str());
	archivo << cadena;
	archivo.close();
}

int XmlParser::getProximoNivel()
{
	//retorna el ultimo numero de nivel almacenado 
	 xmlpp::DomParser parser;
	 parser.parse_file(PATH_CONFIGURACION);
	 int nro = -1;
	 
     if(parser)
     {
     	const xmlpp::Node* pNodoRaiz = parser.get_document()->get_root_node();
     	xmlpp::Node::NodeList listaHijos = pNodoRaiz->get_children();
     	//Tiene un hijo solo
     	const xmlpp::TextNode* nodoTexto = dynamic_cast<const xmlpp::TextNode*> (*(listaHijos.begin()));
     	if (nodoTexto)
     	{
     		std::string contenido = nodoTexto -> get_content();
     		std::istringstream caja(contenido.c_str());
     		caja >> nro;
     	}
     }
     return nro;
}

void XmlParser::actualizarConfiguracion(int nroNivel)
{
	//Si se agrega un nuevo nivel se actualiza el archivo de configuracion
	if (getProximoNivel() == nroNivel) //Se agrego un nuevo nivel
	{
		xmlpp::Document documento;
		xmlpp::Element* nodoRaiz = documento.create_root_node("CantNiveles");
		nroNivel++;
		std::ostringstream caja;
		caja << nroNivel;
	    nodoRaiz->set_child_text(caja.str());
	    
	    //Volcamos todo al archivo
		Glib::ustring cadena = documento.write_to_string();
		std::ofstream archivo(PATH_CONFIGURACION);
		archivo << cadena;
		archivo.close();
	}
}

void XmlParser::armarArchivoEditorMapa(int nroNivel,int alto,int ancho,std::list<RegElemento>& listaEle,std::list<RegElemento>& listaMod)
{
	xmlpp::Document documento;
	xmlpp::Element* nodoRaiz = documento.create_root_node("Mapa");
	
	//Grabamos el ancho y el alto
	std::ostringstream cajaAlto,cajaAncho;
	
	nodoRaiz -> add_child_comment("\n"); //Agrego enter
	xmlpp::Element* nodoHijoAlto = nodoRaiz->add_child("Alto");
	cajaAlto << alto;
	nodoHijoAlto -> set_attribute("Tamanio",cajaAlto.str());
	nodoRaiz -> add_child_comment("\n"); //Agrego enter
	xmlpp::Element* nodoHijoAncho = nodoRaiz->add_child("Ancho");
	cajaAncho << ancho;
	nodoHijoAncho -> set_attribute("Tamanio",cajaAncho.str());
	//Grabamos la lista de Elementos
	for (std::list<RegElemento>::iterator it = listaEle.begin() ; it != listaEle.end() ; it++ )
	{
		std::ostringstream cajaId,cajaRot,cajaFila,cajaColumna;
		int id,rot,f,c;
		
		it -> get(id,rot,f,c);
		nodoRaiz -> add_child_comment("\n"); //Agrego enter
		xmlpp::Element* nodoHijoEle = nodoRaiz->add_child("Elemento");
		cajaId << id;
		nodoHijoEle -> set_attribute("id",cajaId.str());
		cajaRot << rot;
		nodoHijoEle -> set_attribute("rot",cajaRot.str());
		cajaFila << f;
		nodoHijoEle -> set_attribute("fila",cajaFila.str());
		cajaColumna << c;
		nodoHijoEle -> set_attribute("columna",cajaColumna.str());
	}
	//Grabamos la lista de Modificadores
	for (std::list<RegElemento>::iterator it = listaMod.begin() ; it != listaMod.end() ; it++ )
	{
		std::ostringstream cajaId,cajaFila,cajaColumna;
		int id,rot,f,c;
		
		it -> get(id,rot,f,c);
		nodoRaiz -> add_child_comment("\n"); //Agrego enter
		xmlpp::Element* nodoHijoEle = nodoRaiz->add_child("Modificador");
		cajaId << id;
		nodoHijoEle -> set_attribute("id",cajaId.str());
		cajaFila << f;
		nodoHijoEle -> set_attribute("fila",cajaFila.str());
		cajaColumna << c;
		nodoHijoEle -> set_attribute("columna",cajaColumna.str());
	}
	nodoRaiz -> add_child_comment("\n"); //Agrego enter
	//Grabamos en el archivo
	std::string nombre = PATH_MAPA_EDITOR;
	std::ostringstream cajaNro;
	cajaNro << nroNivel;
	nombre += cajaNro.str();
	nombre += ".xml";
	std::ofstream archivo(nombre.c_str());
	Glib::ustring cadena = documento.write_to_string();
	archivo << cadena;
	archivo.close();
}

void XmlParser::parsearArchivoEditorMapa(int nroNivel,int &alto,int &ancho,std::list<RegElemento>& listaEle,std::list<RegElemento>& listaMod)
{
	//Obtenemos el nombre del archivo
	std::string nombre = PATH_MAPA_EDITOR;
	std::ostringstream cajaNro;
	cajaNro << nroNivel;
	nombre += cajaNro.str();
	nombre += ".xml";
	
	//Creamosm el parser y parseamos
	xmlpp::DomParser parser;
	parser.parse_file(nombre);
    if(parser)
    {
    	const xmlpp::Node* pNodoRaiz = parser.get_document()->get_root_node();
    	const xmlpp::ContentNode* contenido = dynamic_cast<const xmlpp::ContentNode*>(pNodoRaiz);
    	if (!contenido)
    	{
    		xmlpp::Node::NodeList listaHijos = pNodoRaiz->get_children();
    		for(xmlpp::Node::NodeList::iterator it = listaHijos.begin(); it != listaHijos.end(); ++it)
    		{
      			const xmlpp::Element* elemento = dynamic_cast<const xmlpp::Element*>(*it);
      			//const xmlpp::CommentNode* comentario = dynamic_cast<const xmlpp::CommentNode*>(*it);
      			//Los comentarios se ignoran
      			if ( (elemento) )//&& (!comentario) )
      			{
      				Glib::ustring nombreEle = (*it)->get_name();
      				if ( (nombreEle == "Ancho") || (nombreEle == "Alto") )
      				{
      					const xmlpp::Element::AttributeList& atributos = elemento->get_attributes();
      					std::istringstream caja( (*(atributos.begin())) -> get_value() );
      					if  (nombreEle == "Ancho")
      						caja >> ancho;
      					else
      						caja >> alto;
      				}
      				if ( (nombreEle == "Elemento") || (nombreEle == "Modificador") )
      				{
      					int nroImg,r,f,c;
      					std::istringstream cajaNro,cajaRot,cajaF,cajaC;
      					const xmlpp::Element::AttributeList& atributos = elemento->get_attributes();
      					for(xmlpp::Element::AttributeList::const_iterator itA = atributos.begin(); itA != atributos.end(); ++itA)
      					{
      						
      						if ( (*itA) -> get_name() == "id" )
      							cajaNro.str ( (*itA) -> get_value() );
      						if ( (*itA) -> get_name() == "rot" )
      							cajaRot.str ( (*itA) -> get_value() );
      						if ( (*itA) -> get_name() == "fila" )
      							cajaF.str ( (*itA) -> get_value() );
      						if ( (*itA) -> get_name() == "columna" )
      							cajaC.str ( (*itA) -> get_value() );
      					}
      						cajaNro >> nroImg;
      						if (nombreEle == "Elemento")
      							cajaRot >> r;
      						else
      							r = 0;
      						cajaF >> f;
      						cajaC >> c;
      						
      						RegElemento R(nroImg,r,f,c);
      						if (nombreEle == "Elemento")
      							listaEle.push_back(R);
      						else
      							listaMod.push_back(R);
      					
      				} 
      				
      			}
    		}
    	}
    }
    
    //-------TODO---------------------------------------------------------------------------
   std::cout << "Ancho: " << ancho << " Alto: " << alto << std::endl;
   for ( std::list<RegElemento>::iterator it = listaEle.begin() ; it != listaEle.end() ; it++)
   {
   		int i,r,f,c;
   		it -> get(i,r,f,c);
   		std:: cout << i << " " << r << " " << f << " " << c << std::endl;
   }
   for ( std::list<RegElemento>::iterator it = listaMod.begin() ; it != listaMod.end() ; it++)
   {
   		int i,r,f,c;
   		it -> get(i,r,f,c);
   		std:: cout << i << " " << r << " " << f << " " << c << std::endl;
   }
   //--------------------------------------------------------------------------------------- 
}
