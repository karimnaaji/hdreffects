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

enum CubeMapFace { 
	POSITIVE_X,
	NEGATIVE_X,
	POSITIVE_Y,
	NEGATIVE_Y,
	POSITIVE_Z,
	NEGATIVE_Z
};

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

		HDRCubeMap();
		~HDRCubeMap();

		void Load(const string& fileName);
	private:
		void LoadFaces();
		int width;
		int height;
		float *data;
	
		Face **faces;
};

#endif
