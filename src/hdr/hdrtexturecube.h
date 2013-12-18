#ifndef HDR_TEXTURE_CUBE_H
#define HDR_TEXTURE_CUBE_H

#include <iostream>
#include <string>
#include <stdexcept>

extern "C" {
	#include "rgbe.h"
}

#include "graphics.h"
#include "texture.h"

struct Face {
	float *data;
	int width;
	int height;
	// for mem copy purposes only
	int currentOffset;
};

class HDRTextureCube : public Texture {
	public:
		HDRTextureCube();
		~HDRTextureCube();

		void Load(const string fileName);
        GLuint Bind();
		void Init();
        void DisposeGL();
	private:
		void LoadFaces();
        void FlipHorizontal(Face* face);
        void FlipVertical(Face* face);

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
