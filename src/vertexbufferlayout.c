#include "renderer.h"
#include "vertexbufferlayout.h"


unsigned int VBE_GetSizeOfType(unsigned int type){
    switch (type) {
    case GL_FLOAT:
        return 4;
        break;
    case GL_UNSIGNED_INT:
        return 4;
        break;
    case GL_UNSIGNED_BYTE:
        return 1;
        break;
    
    default:
        break;
    }
    ASSERT(false);
    return 0;
}


void VBL_Pushfloat(unsigned int count, VertexBufferLayout* VBL){
    VertexBufferElement vbe;
    vbe.count = count;
    vbe.type = GL_FLOAT;
    vbe.normalized = GL_FALSE;

    arrput(VBL->Elements, vbe);
    VBL->stride += VBE_GetSizeOfType(GL_FLOAT) * count;
    
}

void VBL_PushUint(unsigned int count, VertexBufferLayout* VBL){
    VertexBufferElement vbe;
    vbe.count = count;
    vbe.type = GL_UNSIGNED_INT;
    vbe.normalized = GL_FALSE;

    arrput(VBL->Elements, vbe);
    VBL->stride += VBE_GetSizeOfType(GL_UNSIGNED_INT) * count;

}

void VBL_PushUchar(unsigned int count, VertexBufferLayout* VBL){
    VertexBufferElement vbe;
    vbe.count = count;
    vbe.type = GL_UNSIGNED_BYTE;
    vbe.normalized = GL_TRUE;

    arrput(VBL->Elements, vbe);
    VBL->stride += VBE_GetSizeOfType(GL_UNSIGNED_BYTE) * count;

}

unsigned int VBL_GetStride(VertexBufferLayout* VBL){
    return VBL->stride;
}

VertexBufferElement* VBL_GetElements(VertexBufferLayout* VBL){
    return VBL->Elements;
}

void VBL_Construct(VertexBufferLayout* vbl){
    vbl->Elements = NULL;
    vbl->stride = 0;

}