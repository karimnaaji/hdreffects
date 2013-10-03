#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <cmath>

#include "utils.h"
#include "debug.h"

using namespace std;

enum MeshBuffer { 
	VERTEX_BUFFER,
	COLOUR_BUFFER,
    INDEX_BUFFER,
	TEXTURE_BUFFER,
	BUFFER_COUNT
};

#endif
