/* StrToken
* Implementacion Independiente
* Archivo : strToken.cpp
* Version : 2.0
*/

#include "StrToken.h"

/******************************************************************************/
/* Implementacion */
/*------------------------------*/

//Template que convierte de string al tipo Type.
template <class Type> 
bool StrToken::stringTo(Type& tipo,const std::string& s)
{
    std::istringstream iss(s);
    return !(iss >> tipo).fail();
}
/*----------------------------------------------------------------------------*/
tVecStr StrToken::getStrTokens(string cadena,string delimeter)
{
    tVecStr strToken;
    string subCadena="";
    string::size_type posDelimeter=string::npos;
    while(cadena.find(delimeter)!= string::npos)
    {
        posDelimeter = cadena.find_first_of(delimeter);
        subCadena = cadena.substr(0,posDelimeter);
        posDelimeter+=(delimeter.length()-1);       
        strToken.push_back(subCadena);
        cadena = cadena.substr(posDelimeter+1);
    }
    strToken.push_back(cadena);
    return strToken;
}
/*----------------------------------------------------------------------------*/
void StrToken::setTokensParams(tVecStr strTok,char *formato,...)
{
    va_list p; 
    char *szarg; 
    int* iarg; 
    string* strarg;
    double* darg;
    bool* barg;

    va_start(p, formato); 
    //analizamos la cadena de formato para saber el numero y tipo de los 
    //parametros
    for(size_t i = 0; i < strlen(formato); i++) 
    { 
        string cadena=strTok[i];
        switch(formato[i]) 
        { 
        case 'c': /* Cadena de caracteres */ 
            szarg = va_arg(p, char*); 
            StrToken::stringTo<char>(*szarg,cadena);
            break; 
        case 'i': /* Entero */ 
            iarg = va_arg(p, int*); 
            StrToken::stringTo<int>(*iarg,cadena); 
            break; 
        case 's': /* String */ 
            strarg = va_arg(p, string*); 
            *strarg=cadena; 
            break; 
        case 'd': /* Double */ 
            darg = va_arg(p, double*); 
            StrToken::stringTo<double>(*darg,cadena); 
            break;
        case 'b': /* Bool */ 
        	barg = va_arg(p, bool*); 
            StrToken::stringTo<bool>(*barg,cadena);
            break;
        } 
    } 
    va_end(p); 
}
/*----------------------------------------------------------------------------*/
void StrToken::toUpperString(std::string& str)
{
    std::transform(str.begin(),str.end(),str.begin(),::toupper);
}
/*----------------------------------------------------------------------------*/
std::string StrToken:: intToString( int entero )
{

    std::stringstream cadena(""); 
    cadena << entero;
    return cadena.str();
}

