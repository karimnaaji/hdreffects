#ifndef HELPERS_H
#define HELPERS_H

#define HDR_RELATIVE_PATH    	"media/hdr/"
#define OBJ_RELATIVE_PATH       "media/obj/"
#define SHADERS_RELATIVE_PATH   "shaders/"

#define VERT_EXT 	".vert"
#define FRAG_EXT 	".frag"
#define HDR_EXT		".hdr"
#define OBJ_EXT     ".obj"

static const float PI = 3.14159265358979323846f;	
static const float PI_2 = PI / 2.0f;
static const float PI_4 = PI / 4.0f;
static const float PI_360 = PI / 360.0f;

static inline float rad2deg(float theta) {
	return theta / PI * 180.0f;
}

static inline float deg2rad(float theta) {
	return theta * 180.0f / PI;
}

static inline float clamp(float x, float a, float b) {
	return x < a ? a : (x > b ? b : x);
}

static inline float max(float a, float b) {
    return a > b ? a : b;
}

#endif
