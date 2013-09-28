#ifndef HDR_RAW_IMAGE_H
#define HDR_RAW_IMAGE_H

#include <iostream>
#include <string>

#include "rgbe.h"

using namespace std;

class HDR_Raw_Image {
	public:
		HDR_Raw_Image();
		~HDR_Raw_Image();

		void Load(const string& fileName);
	private:
		int width;
		int height;
};

#endif