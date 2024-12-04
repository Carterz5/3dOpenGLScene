#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H


typedef struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

} VertexBufferElement;

typedef struct VertexBufferLayout {
    //use arrput
    VertexBufferElement* Elements;
    unsigned int stride;
} VertexBufferLayout;


unsigned int VBE_GetSizeOfType(unsigned int type);
void VBL_Pushfloat(unsigned int count, VertexBufferLayout* VBL);
void VBL_PushUint(unsigned int count, VertexBufferLayout* VBL);
void VBL_PushUchar(unsigned int count, VertexBufferLayout* VBL);
unsigned int VBL_GetStride(VertexBufferLayout* VBL);
VertexBufferElement* VBL_GetElements(VertexBufferLayout* VBL);
void VBL_Construct(VertexBufferLayout* vbl);

#endif