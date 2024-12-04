#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H


typedef struct IndexBuffer {
    unsigned int RendererID;
    unsigned int Count;

} IndexBuffer;

void IB_Construct(const unsigned int* data, unsigned int count, IndexBuffer* IndexBuffer);
void IB_Populate(unsigned int objectcount, unsigned int* indices, unsigned int arraysize);
void IB_Destruct(IndexBuffer* IndexBuffer);
void IB_Bind(IndexBuffer* IndexBuffer);
void IB_Unbind();
unsigned int IB_Count(IndexBuffer* IndexBuffer);

#endif