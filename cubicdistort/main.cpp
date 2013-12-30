#include <stdio.h>
#include <stdlib.h>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#define kTextureDim 64

GLuint t1;

GLuint makeCheckTex() {
    GLubyte image[kTextureDim][kTextureDim][4]; // RGBA storage

    for (int i = 0; i < kTextureDim; i++) {
        for (int j = 0; j < kTextureDim; j++) {
            int c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0))*255;
            image[i][j][0]  = (GLubyte)c;
            image[i][j][1]  = (GLubyte)c;
            image[i][j][2]  = (GLubyte)c;
            image[i][j][3]  = (GLubyte)255;
        }
    }

    GLuint texName;
    glGenTextures(1, &texName);    
    glBindTexture(GL_TEXTURE_2D, texName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, kTextureDim, kTextureDim, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    return texName;
}

void loadShader() {
    const GLchar* source = "uniform sampler2D renderTexture;\
                            vec2 resolution = vec2(512.0, 512.0);\
                            \
                            float k = -0.75;\
                            float dispersion = 0.03;\
                            float scale = 0.9;\
                            float etaR = 0.9, etaG = 0.6, etaB = 0.2;\
                            float kcube = 0.5;\
                            \
                            void main(void) {\
                            vec2 uv = gl_FragCoord.xy / resolution;\
                            vec3 eta = vec3(1.0 + dispersion * etaR, 1.0 + dispersion * etaG, 1.0 + dispersion * etaB);\
                            vec3 color = vec3(0.0); \
                            \
                            float r2 = (uv.x - 0.5) * (uv.x - 0.5) + (uv.y - 0.5) * (uv.y - 0.5);   \
                            float f = 1.0 + r2 * (k + kcube * sqrt(r2));\
                            \
                            vec2 ruv = (f * eta.r) * scale * (uv.xy - 0.5) + 0.5;\
                            vec2 guv = (f * eta.g) * scale * (uv.xy - 0.5) + 0.5;\
                            vec2 buv = (f * eta.b) * scale * (uv.xy - 0.5) + 0.5;\
                            \
                            color.r = texture2D(renderTexture, ruv).r;\
                            color.g = texture2D(renderTexture, guv).g;\
                            color.b = texture2D(renderTexture, buv).b;\
                            \
                            float d = length(uv - vec2(0.5));\
                            color *= clamp(1.0 - d*d, 0.0, 1.0);\
                            \
                            gl_FragColor = vec4(color, 1.0);\
                            }";

    GLuint program = glCreateProgram();
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint logLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar* log = (GLchar*)malloc(logLength);
        glGetShaderInfoLog(shader, logLength, &logLength, log);
        printf("Shader compile log:\n%s\n", log);
        free(log);
    }

    glAttachShader(program, shader);  
    glLinkProgram(program);

    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar* log = (GLchar*)malloc(logLength);
        glGetProgramInfoLog(program, logLength, &logLength, log);
        printf("Program link log:\n%s\n", log);
        free(log);
    }

    GLuint t1Location = glGetUniformLocation(program, "renderTexture");

    glUniform1i(t1Location, 0);

    glUseProgram(program);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    t1 = makeCheckTex();

    loadShader();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, t1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(-2.0, -2.0);
    glTexCoord2f(0, 2.0);
    glVertex2f(-2.0, 2.0);
    glTexCoord2f(2.0, 2.0);
    glVertex2f(2.0, 2.0);
    glTexCoord2f(2.0, 0);
    glVertex2f(2.0, -2.0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2, 2, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("GLSL Texture Blending");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);

    init();

    glutMainLoop();
    return 0;
}