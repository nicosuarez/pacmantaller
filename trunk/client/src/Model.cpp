#include "Model.h"


Model::Model() : Points((Coordenada*)0), UVs((UV*)0), Normals((Coordenada*)0),Tris((Triangle*)0), indSize(0), uvSize(0), norSize(0), triSize(0),tex((Texture*)0), mat((Material*)0) 
{

}


Model::~Model() 
{
	if (indSize > 0) {		
		delete[] Points;
	}

	if (uvSize > 0) {		
		delete[] UVs;
	}

	if (norSize > 0) {		
		delete[] Normals;
	}

	if (triSize > 0) {		
		delete[] Tris;
	}

	if (tex != 0) {
		delete tex;
	}

	if (mat != 0) {
		delete mat;
	}
}


Texture::Texture() : id(0), data((GLubyte*)0), width(0), height(0), size(0), repT(true), repS(true)
{
}


Texture::~Texture()
{
	if (data != 0) {
		delete[] data;
	}
}

