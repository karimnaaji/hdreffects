#include "hdrcubemap.h"

HDRCubeMap::HDRCubeMap() {
	
}

HDRCubeMap::~HDRCubeMap() {
	for(int i = 0; i < 6; ++i) {
		delete[] faces[i]->data;
		delete faces[i];
	}
	delete[] faces;
	delete[] data;
}

void HDRCubeMap::Load(const string& fileName) {
	FILE* file = fopen(fileName.c_str(), "rb");
	
	RGBE_ReadHeader(file, &width, &height, NULL);
	data = new float[3 * width * height];
	RGBE_ReadPixels_RLE(file, data, width, height);
	
	fclose(file);

	LoadFaces();
	GenerateTextureCube();
}

void HDRCubeMap::LoadFaces() {
	faces = new Face*[6];
	
	int faceWidth = width / 3;
	int faceHeight = height / 4;
	
	for(int i = 0; i < 6; ++i) {
		faces[i] = new Face();
		faces[i]->data = new float[3 * faceWidth * faceHeight];
		faces[i]->width = faceWidth;
		faces[i]->height = faceHeight;
		faces[i]->currentOffset = 0;
	}
	
	for(int l = 0; l < height; ++l) {
		int jFace = (l - (l % faceHeight)) / faceHeight;
		
		for(int iFace = 0; iFace < 3; ++iFace) {
			Face *face = NULL;			
			int offset = 3 * (faceWidth * iFace + l * width);

			if(iFace == 1 && jFace == 0) face = faces[0]; // POS_X
			if(iFace == 1 && jFace == 2) face = faces[1]; // NEG_X
			if(iFace == 2 && jFace == 1) face = faces[2]; // POS_Y
			if(iFace == 0 && jFace == 1) face = faces[3]; // NEG_Y
			if(iFace == 1 && jFace == 1) face = faces[4]; // POS_Z
			if(iFace == 1 && jFace == 3) face = faces[5]; // NEG_Z

			if(face) {
				// the number of components to copy
				int n = sizeof(float) * faceWidth * 3;
				
				memcpy(face->data + face->currentOffset, data + offset, n); 	
				face->currentOffset += (3 * faceWidth);
			}
		}
	}

/*
        int i = 2;      
    GLuint textureId;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    GLenum internalFormat = GL_RGB16F_ARB;

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, faces[i]->width, faces[i]->height, 0, Format, GL_FLOAT, faces[i]->data);                

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);
*/
}

void HDRCubeMap::Bind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
}

void HDRCubeMap::GenerateTextureCube() {
	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	
	for(int i = 0; i < 6; ++i) {
		Face *f = faces[i];
		glTexImage2D(CubeMapFace[i], 0, InternalFormat, f->width, f->height, 0, Format, Type, f->data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
