#include "hdrimage.h"

HDRImage::HDRImage() {
	
}

HDRImage::~HDRImage() {
	
}

void HDRImage::Load(const string& fileName) {
	FILE* file = fopen(fileName.c_str(), "rb");
	
	RGBE_ReadHeader(file, &width, &height, NULL);
	data = new float[sizeof(float) * 3 * width * height];
	RGBE_ReadPixels_RLE(file, data, width, height);
	
	cout << "width : " << width << ", height : " << height << endl;
	
	fclose(file);
}
