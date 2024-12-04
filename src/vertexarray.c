#include "renderer.h"
#include "vertexarray.h"


void VA_Construct(VertexArray* va){

    GLCall(glGenVertexArrays(1, &va->RendererID));

};

void VA_Destruct(VertexArray* va){

    GLCall(glDeleteVertexArrays(1, &va->RendererID));

};



void VA_AddBuffer(VertexBuffer* vb, VertexBufferLayout* layout, VertexArray* va){

    VA_Bind(va);
    VB_Bind(vb);
    unsigned int offset = 0;

    for (int i = 0; i < arrlen(layout->Elements); i++){
        VertexBufferElement element = layout->Elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout->stride, (const void*)offset));
        offset += element.count * VBE_GetSizeOfType(element.type);
    }
}

void VA_Bind(VertexArray* va){

    GLCall(glBindVertexArray(va->RendererID));

};
void VA_Unbind(){

    GLCall(glBindVertexArray(0));

};