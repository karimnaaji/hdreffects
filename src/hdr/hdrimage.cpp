#include "hdrimage.h"

HDRImage::HDRImage() {
	
}

HDRImage::~HDRImage() {
	
}

void HDRImage::Load(const string& fileName) {
	FILE* file = fopen(fileName.c_str(), "rb");

	if (file == 0)
        throw std::runtime_error("hdr resource not found : " + fileName + ".");
	
	RGBE_ReadHeader(file, &width, &height, 0);
	data = new float[sizeof(float) * 3 * width * height];
	RGBE_ReadPixels_RLE(file, data, width, height);

	fclose(file);
}