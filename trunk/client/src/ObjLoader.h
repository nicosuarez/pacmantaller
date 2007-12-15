#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include <vector>
#include "Model.h"

class ObjLoader {

	private:
		static int ParseObj(FILE* file, std::vector<Coordenada>& points, std::vector<UV>& uvs, std::vector<Coordenada>& normals, std::vector<Triangle>& triangles);
		static GLubyte* ReadTga(const char* name, unsigned& size, unsigned& bpp, unsigned& w, unsigned& h);
		static void CreateBoundingBox(Model &model);

	public:
		static int cargarModelo(Model &model, const char *obj_filename, const char *tga_filename);

};

#endif /*OBJLOADER_H_*/
