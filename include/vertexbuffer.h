#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H




typedef struct VertexBuffer {
    unsigned int RendererID;
    unsigned int offset;

} VertexBuffer;

void VB_Construct(const void* data, unsigned int size, VertexBuffer* VertexBuffer);
void VB_Construct_Batch(unsigned int size, VertexBuffer* VertexBuffer);
void VB_AddToBatch(VertexBuffer* VertexBuffer, unsigned int size, void* data);
void VB_Destruct(VertexBuffer* VertexBuffer);
void VB_Bind(VertexBuffer* VertexBuffer);
void VB_Unbind();

#endif