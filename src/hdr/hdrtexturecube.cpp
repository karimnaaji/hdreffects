#include "hdrtexturecube.h"

HDRTextureCube::HDRTextureCube(int textureIndex_) : textureIndex(textureIndex_) 
{}

HDRTextureCube::~HDRTextureCube() {
	glDeleteTextures(6, &textureId);

	for(int i = 0; i < 6; ++i) {
		delete[] faces[i]->data;
		delete faces[i];
	}
	delete[] faces;
	delete[] data;
}

void HDRTextureCube::Load(const string fileName) {
	string path = string(MEDIA_RELATIVE_PATH) + fileName + string(HDR_EXT);	

	cout << "Loading hdr texture.. [" << fileName << "]" << endl;

	FILE* file = fopen(path.c_str(), "rb");
	
	RGBE_ReadHeader(file, &width, &height, NULL);
	data = new float[3 * width * height];
	RGBE_ReadPixels_RLE(file, data, width, height);
	
	fclose(file);

	LoadFaces();

	cout << " - width : " << width << "px" << endl; 
	cout << " - height : " << height << "px" << endl;
	cout << " - memory size : " << (3 * width * height * sizeof(float)) / 8 << " bytes" << endl;

	cout << endl;

	cout << "Generating texture cube.." << endl;

	Generate();
}

void HDRTextureCube::LoadFaces() {
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

			if(iFace == 2 && jFace == 1) face = faces[0]; // POS_Y
			if(iFace == 0 && jFace == 1) face = faces[1]; // NEG_Y
			if(iFace == 1 && jFace == 0) face = faces[2]; // POS_X
			if(iFace == 1 && jFace == 2) face = faces[3]; // NEG_X
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

    // adjust NEG_Z face
    FlipHorizontal(faces[5]); 
    FlipVertical(faces[5]);   
}

void HDRTextureCube::FlipHorizontal(Face* face) {
    int dataSize = face->width * face->height * 3;
    int n = sizeof(float) * 3 * face->width;
    float* newData = new float[dataSize];

    for(int i = 0; i < face->height; i++) {
        int offset = i * face->width * 3;
        int bias = -(i + 1) * 3 * face->width;

        memcpy(newData + dataSize + bias, face->data + offset, n);
    }

    delete[] face->data;
    face->data = newData;
}

void HDRTextureCube::FlipVertical(Face* face) {
    int dataSize = face->width * face->height * 3;
    int n = sizeof(float) * 3;
    float* newData = new float[dataSize];

    for(int i = 0; i < face->height; ++i) {
        int lineOffset = i * face->width * 3;

        for(int j = 0; j < face->width; ++j) {
            int offset = lineOffset + j * 3;
            int bias = lineOffset + face->width * 3 - (j + 1) * 3;
            
            memcpy(newData + bias, face->data + offset, n);
        }   
    }

    delete[] face->data;
    face->data = newData;
}

GLuint HDRTextureCube::TextureId() const {
	return textureId;
}

GLuint HDRTextureCube::TextureIndex() const {
	return textureIndex;
}

GLuint HDRTextureCube::Bind() {
	glActiveTexture(GL_TEXTURE0 + textureIndex);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	return textureId;
}

void HDRTextureCube::Generate() {
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	cout << endl;
	cout << "HDR Texture parameters : " << endl;
	cout << " - Format: " << ((Format == GL_RGB) ? "RGB" : "") << endl;
	cout << " - Type : " << ((Type == GL_FLOAT) ? "Float" : "") << endl;
	cout << " - Internal Format : " << ((InternalFormat == GL_RGB8) ? "RGB8" : "RGB16F") << endl;
	cout << endl;

	for(int i = 0; i < 6; ++i) {
		Face *f = faces[i];
		glTexImage2D(CubeMapFace[i], 0, InternalFormat, f->width, f->height, 0, Format, Type, f->data);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
