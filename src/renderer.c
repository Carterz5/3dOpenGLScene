#include "renderer.h"
#include <stdbool.h>
#include <stdio.h>
#include "texture.h"



void GLClearError(){
    while(glGetError() != GL_NO_ERROR);
};


bool GLLogCall(const char* function, const char* file, int line){
    GLenum error;
    while(error = glGetError()){
        
        printf("[OpenGL Error] (%d): %s, file: %s, line: %d\n", error, function, file, line);
        return false;
    }
    return true;
}

void R_CreateQuad(Quad* quad, float x, float y, float textureID, float r, float g, float b, float a, float size){

    quad->v0.Position[0] = x;
    quad->v0.Position[1] = y;
    quad->v0.Position[2] = 0.0f;
    quad->v0.Color[0] = r;
    quad->v0.Color[1] = g;
    quad->v0.Color[2] = b;
    quad->v0.Color[3] = a;
    quad->v0.TexCoords[0] = 0.0f;
    quad->v0.TexCoords[1] = 0.0f;
    quad->v0.TexID = textureID;

    quad->v1.Position[0] = x + size;
    quad->v1.Position[1] = y;
    quad->v1.Position[2] = 0.0f;
    quad->v1.Color[0] = r;
    quad->v1.Color[1] = g;
    quad->v1.Color[2] = b;
    quad->v1.Color[3] = a;
    quad->v1.TexCoords[0] = 1.0f;
    quad->v1.TexCoords[1] = 0.0f;
    quad->v1.TexID = textureID;

    quad->v2.Position[0] = x + size;
    quad->v2.Position[1] = y + size;
    quad->v2.Position[2] = 0.0f;
    quad->v2.Color[0] = r;
    quad->v2.Color[1] = g;
    quad->v2.Color[2] = b;
    quad->v2.Color[3] = a;
    quad->v2.TexCoords[0] = 1.0f;
    quad->v2.TexCoords[1] = 1.0f;
    quad->v2.TexID = textureID;

    quad->v3.Position[0] = x;
    quad->v3.Position[1] = y + size;
    quad->v3.Position[2] = 0.0f;
    quad->v3.Color[0] = r;
    quad->v3.Color[1] = g;
    quad->v3.Color[2] = b;
    quad->v3.Color[3] = a;
    quad->v3.TexCoords[0] = 0.0f;
    quad->v3.TexCoords[1] = 1.0f;
    quad->v3.TexID = textureID;



}

void R_Draw(VertexArray* va, IndexBuffer* ib, Shader* shader){

    SH_Bind(shader);
    VA_Bind(va);
    IB_Bind(ib);

    GLCall(glDrawElements(GL_TRIANGLES, ib->Count, GL_UNSIGNED_INT, NULL));

};

void R_Clear(){

    GLCall(glClear(GL_COLOR_BUFFER_BIT));

}