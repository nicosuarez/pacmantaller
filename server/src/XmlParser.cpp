#include "XmlParser.h"

XmlParser::XmlParser()
{
}

vector<int> XmlParser::elementosNoPastillas;

void XmlParser::setAncho(Mapa* mapa,xmlpp::TextReader& reader)
{
	int ancho=0;
	ancho=getAtributoInt(reader,ATRIB_VALOR);
	if(ancho!=-1)
		mapa->setAncho(ancho);
	std::cout<<ATRIB_VALOR << ": "<< ancho << "\n";
}
/*----------------------------------------------------------------------------*/
void XmlParser::setAlto(Mapa* mapa,xmlpp::TextReader& reader)
{
	int alto=0;
	alto=getAtributoInt(reader,ATRIB_VALOR);
	if(alto!=-1)
		mapa->setAlto(alto);
	std::cout<<ATRIB_VALOR << ": "<< alto << "\n";
}
/*----------------------------------------------------------------------------*/
int XmlParser::getAtributoInt(xmlpp::TextReader& reader,string atrib)
{
	int intValor=-1;
	StrToken::stringTo<int>(intValor,reader.get_attribute (atrib));	
	return intValor;
}
/*----------------------------------------------------------------------------*/
tVertice* XmlParser::agregarVertice(Mapa* mapa,int idVertice)
{
	tVertice* vertice = mapa->getGrafo()->getVertice(idVertice);
    if(vertice==NULL)
    {
    	//Setea el elemento del vertice como NULL.
    	//Al final se cargan todos los elementos en el mapa
        vertice =mapa->getGrafo()->agregarVertice(idVertice,NULL);
    }
    return vertice;
}
/*----------------------------------------------------------------------------*/
Orientacion XmlParser::orientacionParser(string orientacion)
{
	if(orientacion == OESTE)
		return Oeste;
	if(orientacion == SUR)
		return Sur;
	if(orientacion == NORTE)
		return Norte;
	if(orientacion == ESTE)
		return Este;
	return Norte;
}
/*----------------------------------------------------------------------------*/
Orientacion XmlParser::getOrientacionContraria(string orientacion)
{
	if(orientacion == OESTE)
		return Este;
	if(orientacion == SUR)
		return Norte;
	if(orientacion == NORTE)
		return Sur;
	if(orientacion == ESTE)
		return Oeste;
	return Norte;
}
/*----------------------------------------------------------------------------*/
void readElement(xmlpp::TextReader& reader,string elem)
{
	do
	{
		reader.read();
	}while(elem!=reader.get_name());
}
/*----------------------------------------------------------------------------*/
void XmlParser::cargarPasillo(Mapa* mapa,int arcoId,string orientacion,int vIdOrig,int vIdDest)
{
	tVertice* vDest=NULL;
	tVertice* vOrig=NULL;
	
	//Agrego Vertice Origen:
	vOrig = agregarVertice(mapa,vIdOrig);
	//Agrego Vertice Origen:
	vDest = agregarVertice(mapa,vIdDest);
	//Agrego Arista al Mapa:
	
	//Via doble mano...
    tArco* ida = (vOrig)->getArco(arcoId);
    tArco* vuelta = (vDest)->getArco(arcoId);

    //Si no existen los arcos se agregan.
    if(ida==NULL)
    {
    	mapa->getGrafo()->agregarArco(vOrig,vDest,arcoId,orientacionParser(orientacion));
    	std::cout << arcoId<<","<<vIdOrig<<","<<vIdDest<<","<< orientacion << std::endl;
    }
    if(vuelta==NULL)
    {
    	mapa->getGrafo()->agregarArco(vDest,vOrig,arcoId,getOrientacionContraria(orientacion));
    	std::cout << arcoId<<","<<vIdDest<<","<<vIdOrig<<","<< 
    	LogResource::getOrientacionContraria(orientacion)<< std::endl;;
    }
}
/*----------------------------------------------------------------------------*/
void XmlParser::cargarArista(Mapa* mapa,xmlpp::TextReader& reader,int arcoId,string orientacion)
{
	int idVerticeOrig=0;
	int idVerticeDest=0;

	readElement(reader,VERTICE);
	idVerticeOrig = getAtributoInt(reader,ATRIB_ID);
	readElement(reader,VERTICE);
	idVerticeDest = getAtributoInt(reader,ATRIB_ID);
	
	cargarPasillo(mapa,arcoId,orientacion,idVerticeOrig,idVerticeDest);
}
/*----------------------------------------------------------------------------*/
void XmlParser::agregarArista(Mapa* mapa,xmlpp::TextReader& reader)
{
	int arcoId=-1;	
	
	string orientacion = reader.get_attribute (ATRIB_ORIENTACION);
	arcoId=getAtributoInt(reader,ATRIB_ID);
	cargarArista(mapa,reader,arcoId,orientacion);
}
/*----------------------------------------------------------------------------*/
void XmlParser::buscarElemento(xmlpp::TextReader& reader)
{
	int nodeType = (int)reader.get_node_type();
		   
	//Busca un nodo tipo Elemento.
	while(nodeType!=1 && nodeType!=0)
	{
		reader.read();
		nodeType = (int)reader.get_node_type();
	}
}
/*----------------------------------------------------------------------------*/
void XmlParser::cargarGrafo(Mapa* mapa,xmlpp::TextReader& reader)
{
	std::string name="";
	do
    {
		buscarElemento(reader);
		mostrarNombre(reader);	
		name = reader.get_name();
		if(name==ARISTA)
			agregarArista(mapa,reader);
        
    }while(reader.read() && name!=ELEMENTOS);
}
/*----------------------------------------------------------------------------*/
void XmlParser::agregarPowerUp(Mapa* mapa,xmlpp::TextReader& reader)
{
	int idVertice = getAtributoInt(reader,ATRIB_ID_VERTICE);
	PowerUp* powerUp=new PowerUp(idVertice);
	Modelo::getInstance()->GetElementos()->push_back(powerUp);
	elementosNoPastillas.push_back(idVertice);
	std::cout << POWER_UP << " " << ATRIB_ID << ": " << idVertice << "\n";
}
/*----------------------------------------------------------------------------*/
void XmlParser::agregarBonus(Mapa* mapa,xmlpp::TextReader& reader)
{
	int idVertice = getAtributoInt(reader,ATRIB_ID_VERTICE);
	Bonus* bonus=new Bonus(idVertice);
	Modelo::getInstance()->GetElementos()->push_back(bonus);
	elementosNoPastillas.push_back(idVertice);
	std::cout << BONUS << " " << ATRIB_ID << ": " << idVertice << "\n";
}
/*----------------------------------------------------------------------------*/
void XmlParser::agregarSalidaPacMan(Mapa* mapa,xmlpp::TextReader& reader)
{
	int idVertice = getAtributoInt(reader,ATRIB_ID_VERTICE);
	SalidaPacMan salida(idVertice);
	Modelo::getInstance()->SetSalidaPacMan(salida);
	elementosNoPastillas.push_back(idVertice);
	std::cout << SALIDA_PACMAN << " " << ATRIB_ID << ": " << idVertice << "\n";
}
/*----------------------------------------------------------------------------*/
void XmlParser::agregarCasaFantasmas(Mapa* mapa,xmlpp::TextReader& reader)
{
	int idVertice=0;
	int idPuerta = getAtributoInt(reader,ATRIB_ID_VERTICE);
	elementosNoPastillas.push_back(idPuerta);
	//tVertice* vPuertaCasa = mapa->getGrafo()->getVertice(idPuerta);
	std::cout << CASA_FANTASMAS << " " << "Entrada" << ": " << idPuerta << "\n";
	for(int i=1;i<7;i++)
	{
		idVertice=getAtributoInt(reader,ATRIB_ID_VERTICE+StrToken::intToString(i));
		elementosNoPastillas.push_back(idVertice);
		std::cout << CASA_FANTASMAS << " " << ATRIB_ID << ": " << idVertice << "\n";
	}	
	string orientacion=reader.get_attribute(ATRIB_ORIENTACION);
	std::cout << ATRIB_ORIENTACION << ": " << orientacion << "\n";
	CasaFantasmas casaFantasmas(idPuerta,orientacionParser(orientacion));
	Modelo::getInstance()->SetCasaFantasmas(casaFantasmas);
}
/*----------------------------------------------------------------------------*/
bool XmlParser::agregarPastilla(int idVertice)
{
	bool esta=false;
	for(size_t i=0;i<elementosNoPastillas.size();i++)
	{
		if(elementosNoPastillas[i]==idVertice)
		{
			esta=true;
			break;
		}
	}
	return !esta;
}
/*----------------------------------------------------------------------------*/
void XmlParser::agregarPastillas(Mapa* mapa)
{
	int idVertice=-1;
	tItVertice it;
	tListaVertice* lVertices = mapa->getGrafo()->getVertices();
	
	for(it=lVertices->begin();it!=lVertices->end();it++)
	{
		idVertice=(*it)->getid();
		if(agregarPastilla(idVertice))
		{
			Pastilla* pastilla = new Pastilla(idVertice);
			Modelo::getInstance()->GetElementos()->push_back(pastilla);
			std::cout << PASTILLAS << " " << ATRIB_ID << ": " << idVertice << "\n";
		}
	}
}
/*----------------------------------------------------------------------------*/
void XmlParser::agregarElementos(Mapa* mapa,xmlpp::TextReader& reader)
{
	do
    {   
		string tipoElemento = reader.get_attribute(ATRIB_TIPO);
		if(tipoElemento==POWER_UP)
			agregarPowerUp(mapa,reader);
		if(tipoElemento==BONUS)
			agregarBonus(mapa,reader);
		if(tipoElemento==CASA_FANTASMAS)
			agregarCasaFantasmas(mapa,reader);
		if(tipoElemento==SALIDA_PACMAN)
			agregarSalidaPacMan(mapa,reader);
				
    }while(reader.read());
	
	//Se agregan las pantillas al mapa
	agregarPastillas(mapa);
}
/*----------------------------------------------------------------------------*/
void XmlParser::mostrarNombre(xmlpp::TextReader& reader)
{
	string name = reader.get_name();
	std::cout << "--- Nodo ---" << std::endl;
	std::cout << "Nombre: " << name << std::endl;
}
/*----------------------------------------------------------------------------*/
Mapa* XmlParser::getMapa(string mapaPath)
{
	xmlpp::TextReader reader(mapaPath);
	
	Mapa* mapa = new Mapa;
	while(reader.read())
    {
	  mostrarNombre(reader);
	  std::string name = reader.get_name();
      if(name==ANCHO)
    	  setAncho(mapa,reader);
      else if(name==ALTO)
    	  setAlto(mapa,reader);
      else if(name==GRAFO)
    	  cargarGrafo(mapa,reader);
      else if(name==ELEMENTO)
		  agregarElementos(mapa,reader);  
    }	
	reader.close();
	
	
	/*tListaVertice* vertices;
	tItVertice it;
	vertices = mapa->getGrafo()->getVertices();
	for(it=vertices->begin();it!=vertices->end();it++)
	{
		std::cout<<"Vertice:"<<(*it)->getid()<<"\n";
		//delete (*it);
	}*/
	
	return mapa;
}
/*----------------------------------------------------------------------------*/
void XmlParser::cargarMundo(Mundo* mundo,xmlpp::TextReader& reader)
{
	do
    {   	
		buscarElemento(reader);
		string path = reader.get_attribute(ATRIB_PATH);
		if(path!="")
		{
			std::cout<<"Mostrar path: "<<path<<"\n";
			mundo->getNiveles()->push(path);
		}	
    }while(reader.read());
}
/*----------------------------------------------------------------------------*/
Mundo* XmlParser::getMundo(string mundoPath)
{
	xmlpp::TextReader reader(mundoPath);
		
	Mundo* mundo = new Mundo;
	while(reader.read())
    {
	  mostrarNombre(reader);
	  std::string name = reader.get_name();
      if(name==MAPA)
    	  cargarMundo(mundo,reader);
    }
	reader.close();
	return mundo;
}
/*----------------------------------------------------------------------------*/



