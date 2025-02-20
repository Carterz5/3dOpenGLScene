#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <signal.h>
#include <stdbool.h>
#include "stb_ds.h"
#include "shader.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include "texture.h"

#ifdef _WIN32
    #include <intrin.h>
    #define ASSERT(x) if (!(x)) __debugbreak();
#else
    #define ASSERT(x) if (!(x)) raise(SIGTRAP);
#endif



#define TARGET_FPS 60
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))



typedef struct Vertex {
    float Position[3];
    float Color[4];
    float TexCoords[2];
    float TexID;

} Vertex;

typedef struct Quad {
    Vertex v0;
    Vertex v1;
    Vertex v2;
    Vertex v3;

} Quad;

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
void R_CreateQuad(Quad* quad, float x, float y, float textureID, float r, float g, float b, float a, float size);
void R_Draw_IB(VertexArray* va, IndexBuffer* ib, Shader* shader);
void R_Draw(VertexArray* va, unsigned int count, Shader* shader);
void R_Draw_IB_Instanced(VertexArray* va, IndexBuffer* ib, Shader* shader, unsigned int Icount);
void R_Clear();

#endif