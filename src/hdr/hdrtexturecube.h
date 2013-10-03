#ifndef HDR_TEXTURE_CUBE_H
#define HDR_TEXTURE_CUBE_H

#include <iostream>
#include <string>
#include <stdexcept>

extern "C" {
	#include "rgbe.h"
}

#include "graphics.h"
#include <iostream>

struct Face {
	float *data;
	int width;
	int height;
	// for mem copy purposes only
	int currentOffset;
};

class HDRTextureCube {
	public:
		const GLenum Format = GL_RGB;
		const GLenum Type = GL_FLOAT;
		const GLenum InternalFormat = GL_RGB16F_ARB;
		//const GLenum InternalFormat = GL_RGB8;

		HDRTextureCube(int textureIndex = 0);
		~HDRTextureCube();

		void Load(const string fileName);
		GLuint Bind();
		GLuint TextureId() const;
		GLuint TextureIndex() const;
	private:
		void LoadFaces();
		void Generate();
		int width;
		int height;
		float *data;
		
		GLuint textureId;
		GLuint textureIndex;
		
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
