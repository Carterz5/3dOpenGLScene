#include "renderer.h"
#include "indexbuffer.h"




void IB_Construct(const unsigned int* data, unsigned int count, IndexBuffer* IndexBuffer){
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    IndexBuffer->Count = count;

    GLCall(glGenBuffers(1, &IndexBuffer->RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IB_Destruct(IndexBuffer* IndexBuffer){
    GLCall(glDeleteBuffers(1, &IndexBuffer->RendererID))
};

void IB_Populate(unsigned int objectcount, unsigned int* indices, unsigned int arraysize){
    if((objectcount*6) > arraysize){
        printf("ERROR IN IB_Populate CALL: object count is too high for size of array!\n");
    }
    
    unsigned int loops = 0;
    unsigned int tier = 0;
    for (unsigned int i = 0; i < objectcount*6; i++){
        switch (loops){
        case 3:
            indices[i] = tier + 2;
            loops++;
            break;
        case 4:
            indices[i] = tier + 3;
            loops++;
            break;
        case 5:
            indices[i] = tier;
            tier = tier+4;
            loops = 0;
            break;
        
        default:
            indices[i] = tier + loops;
            loops++;
            break;
        }
    }
    


}

void IB_Bind(IndexBuffer* IndexBuffer){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->RendererID));
};

void IB_Unbind(){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
};

unsigned int IB_Count(IndexBuffer* IndexBuffer){
    return IndexBuffer->Count;
};