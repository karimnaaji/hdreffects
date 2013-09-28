#ifndef HDR_IMAGE_H
#define HDR_IMAGE_H

#include <iostream>
#include <string>
#include <stdexcept>

extern "C" {
	#include "rgbe.h"
}

#include "graphics.h"

using namespace std;

class HDRImage {
	public:
		const GLenum Format = GL_RGB;
		const GLenum Type = GL_FLOAT;

		HDRImage();
		~HDRImage();

		void Load(const string& fileName);
	private:
		int width;
		int height;
		float *data;
};

#endif
