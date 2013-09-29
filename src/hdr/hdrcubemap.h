#ifndef HDR_CUBE_MAP_H
#define HDR_CUBE_MAP_H

#include <iostream>
#include <string>
#include <stdexcept>

extern "C" {
	#include "rgbe.h"
}

#include "graphics.h"

using namespace std;


struct Face {
	float *data;
	int width;
	int height;
	// for mem copy purposes only
	int currentOffset;
};

class HDRCubeMap {
	public:
		const GLenum Format = GL_RGB;
		const GLenum Type = GL_FLOAT;
		const GLenum InternalFormat = GL_RGB16F_ARB;

		HDRCubeMap();
		~HDRCubeMap();

		void Load(const string& fileName);
		void Bind();
	private:
		void LoadFaces();
		void GenerateTextureCube();
		int width;
		int height;
		float *data;
		
		GLuint textureId;
		Face **faces;

		const GLenum CubeMapFace[6] { 
			GL_TEXTURE_CUBE_MAP_POSITIVE_X, 
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 
		};
};

#endif
