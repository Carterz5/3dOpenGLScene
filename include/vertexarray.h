#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

typedef struct VertexArray {
    unsigned int RendererID;

} VertexArray;

void VA_Construct(VertexArray* va);
void VA_Destruct(VertexArray* va);
void VA_AddBuffer(VertexBuffer* vb, VertexBufferLayout* layout, VertexArray* va);
void VA_Bind(VertexArray* va);
void VA_Unbind();


#endif