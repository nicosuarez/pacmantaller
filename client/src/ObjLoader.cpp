#include "ObjLoader.h"

typedef unsigned char byte;

int ObjLoader::ParseObj(FILE* file, std::vector<Coordenada>& points, std::vector<UV>& uvs, std::vector<Coordenada>& normals, std::vector<Triangle>& triangles)
{
	
	int line = 1;//linea actual
	int read = -1;	
	char buffer[2048];//buffer para una linea

	
	while (fgets(buffer, sizeof(buffer), file)) { //lee el obj
		
		const char* linestart = buffer;
		while (isspace(*linestart)) //saltea espacios en blanco
			linestart++;
		
		if (*linestart) {
			
			char first_word[1024];
			read = sscanf(linestart, "%s", first_word);
			// geometric vertices
			if (strcmp(first_word, "v") == 0) {
				
				Coordenada p;
				char extra[64];
				//lee los valores de v
				read = sscanf(linestart, "%s %f %f %f %s", first_word, &p.x, &p.y, &p.z, extra);			
				if (read != 4) return line;//error, no se leen 4 campos: v x y z				
				// agrego coord a la lista points
				points.push_back(p);
			
			// coordenada UV
			} else if (strcmp(first_word, "vt") == 0) {
				
				UV uv;
				char extra[64];				
				read = sscanf(linestart, "%s %f %f %s", first_word, &uv.u, &uv.v, extra);				
				if (read != 3) return line; //error				
				uvs.push_back(uv);

			// vertex normal
			} else if (strcmp(first_word, "vn") == 0) {
				
				Coordenada n;
				char extra[64];				
				read = sscanf(linestart, "%s %f %f %f %s", first_word, &n.x, &n.y, &n.z, extra);			
				if (read != 4) return line;
				normals.push_back(n);
			
			// face triangulo (Elements)
			} else if (strcmp(first_word, "f") == 0) {
				
				Triangle t;
				char extra[64];				
				read = sscanf(linestart, "%s %u/%u/%u %u/%u/%u %u/%u/%u %s", first_word, &t.p0, &t.uv0, &t.n0,
					&t.p1, &t.uv1, &t.n1, &t.p2, &t.uv2, &t.n2, extra);				
				if (read != 10) return line;
				triangles.push_back(t);
			
			} else {		
				return line;
			}

		}		
		line++;
	}
	
	return -1;
}


GLubyte* ObjLoader::ReadTga(const char* name, unsigned& size, unsigned& bpp, unsigned& w, unsigned& h)
{	
	const byte header[12] = {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	byte compare[12];	
	byte next[6];

	memset(compare, 0, sizeof(compare));
	memset(next, 0, sizeof(next));

	unsigned width = 0;
	unsigned height = 0;
	unsigned bitsperpixel = 0;
	unsigned imgsize = 0;
	GLubyte* data = 0;

	char filename[512];	
	strcpy(filename, name);	
	FILE *file = fopen(filename, "rb");

	bool error = false;	
	if (file) {	
		if (fread(compare, 1, sizeof(header), file) == sizeof(header)) {
			if (memcmp(header, compare, sizeof(header)) == 0)
				fread(next, 1, sizeof(next), file);
			else error = true;

		} else error = true;

		if (error) {
			fclose(file);
			file = 0;
			return 0;
		}

	} else return 0;
	
	width  = (next[1] << 8) + next[0];
	height = (next[3] << 8) + next[2];
	bitsperpixel = next[4];

	if (bitsperpixel != 32) {
		fclose(file);
		file = 0;
		return 0;
	}

	imgsize = width * height * (bitsperpixel / 8);
	data = new GLubyte[imgsize];
	if (!data) {
		fclose(file);
		file = 0;
		return 0;
	}
	
	if (fread(data, 1, imgsize, file) != imgsize) {
		delete[] data;
		data = 0;
		fclose(file);
		file = 0;
		return 0;
	}

	unsigned incr = bitsperpixel/8;
	for (unsigned i = 0; i < imgsize; i+= incr) {		
		GLubyte tmp = data[i];
		data[i] = data[i+2];
		data[i+2] = tmp;
	}

	fclose(file);
	file = 0;

	size = imgsize;
	bpp = bitsperpixel;
	w = width;
	h = height;

	cout<<"ok READTGA"<<endl;
	return data;
}


void ObjLoader::CreateBoundingBox(Model &model)
{
	int n = model.indSize;
	int i;
	Coordenada min = model.Points[0];
	Coordenada max = model.Points[0];
	Coordenada v;

	for (i = 1; i < n; i++) {
		v = model.Points[i];
		if (v.x > max.x) {
			max.x = v.x;
		}
		if (v.y > max.y) {
			max.y = v.y;
		}
		if (v.z > max.z) {
			max.z = v.z;
		}
		
		if (v.x < min.x) {
			min.x = v.x;
		}
		if (v.y < min.y) {
			min.y = v.y;
		}
		if (v.z < min.z) {
			min.z = v.z;
		}
	}
	model.Center = (max + min)*0.5f ; 
	model.BBox   = (max - min)*0.5f;
}


int ObjLoader::cargarModelo(Model& model,const char* obj_filename, const char* tga_filename){

	cout<<"obj_filename: "<<obj_filename<<endl;
	std::vector<Coordenada> points;
	std::vector<UV> uvs;
	std::vector<Coordenada> normals;
	std::vector<Triangle> triangles;
	GLubyte* data = NULL;
	unsigned size, w, h, bpp;

	char filename[256];	
	strcpy(filename, obj_filename);
	FILE* input = fopen(filename, "r");
	int r = 0;

	if (input) {
		printf("...cargando .obj: %s.\n", filename);		
		r = ParseObj(input, points, uvs, normals, triangles);
		if (r == -1) {
			r = 0;
		} else {
			printf("Error en la linea: %i\n", r);
			r = r+1;
		}
		fclose(input);

	} else {
		printf("no se puede abrir: %s\n", filename);
		r = 1;
	}

	input = 0;

	if (tga_filename != NULL && r == 0) {
		strcpy(filename, tga_filename);
		printf("...cargando .tga: %s.\n", filename);
		data = ReadTga(tga_filename, size, bpp, w, h);

		if (data == NULL) {
			printf("Error de lectura\n");
			r = 2;
		}
	}

	//no hay error
	if (r == 0) {
		//cout<<"no hay error de tga ni obj"<<endl;
		int n,m,k,l,i;
		
		n = points.size();
		l = uvs.size();
		m = triangles.size();
		k = normals.size();
		model.Points    = new Coordenada[n];
		model.UVs       = new UV[l];
		model.Normals   = new Coordenada[k];
		model.Tris      = new Triangle[m];
		
		//copiar datos
		for (i = 0; i < n; i++) {
			model.Points[i] = points[i];
		}

		for (i = 0; i < l; i++) {
			model.UVs[i] = uvs[i];
		}

		for (i = 0; i < k; i++) {
			model.Normals[i] = normals[i];
		}
		
		for (i = 0; i < m; i++) {
			model.Tris[i] = triangles[i];
		}

		model.indSize = n;
		model.norSize = k;
		model.triSize = m;
		model.uvSize  = l;
		
		cout<<"copie datos"<<endl;		
		if (tga_filename != NULL) {
			cout<<"copio tga"<<endl;
			model.tex = new Texture;
			model.tex->data = (GLubyte*)data;
			model.tex->width = w;
			model.tex->height = h;
			model.tex->size = size;
			glGenTextures (1, &(model.tex->id));
			glBindTexture (GL_TEXTURE_2D, model.tex->id);
			
			glTexImage2D (GL_TEXTURE_2D, 0, 4, model.tex->width, model.tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, model.tex->data);
			
		//	gluBuild2DMipmaps (GL_TEXTURE_2D, 4, model.tex->width, model.tex->height, GL_RGBA, GL_UNSIGNED_BYTE, model.tex->data);
			/*switch (gluBuild2DMipmaps (GL_TEXTURE_2D, 4, model.tex->width, model.tex->height, GL_RGBA, GL_UNSIGNED_BYTE, model.tex->data)) {
				case GLU_INVALID_VALUE:{
					cout<<"width or height are < 1"<<endl;
					break;
					}
				case GLU_INVALID_ENUM: {
					cout<<"internalFormat, format or type are not legal."<<endl;
					break;
				}
				case GLU_INVALID_OPERATION: {
					cout<<"if type is GL_UNSIGNED_BYTE_3_3_2 or GL_UNSIGNED_BYTE_2_3_3_REV and format is not GL_RGB."<<endl;
					break;
				}			
			}*/
		} 
		else {
			model.tex = NULL;
		}
		cout<<"ahora CreateBoundingBox(model);"<<endl;
		CreateBoundingBox(model);
	}
	cout<<"ok OBJloader"<<endl;
	return r;
}
