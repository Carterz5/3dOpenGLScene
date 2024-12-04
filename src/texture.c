#include <stdio.h>
#include "texture.h"
#include "renderer.h"
#include "stb_image.h"



void TX_Construct(char* filepath, Texture* tx){
    tx->RendererID = 0;
    tx->FilePath = filepath;
    tx->LocalBuffer = NULL;
    tx->Width = 0;
    tx->Height = 0;
    tx->BPP = 0;

    stbi_set_flip_vertically_on_load(1);
    tx->LocalBuffer = stbi_load(filepath, &tx->Width, &tx->Height, &tx->BPP, 4);

    GLCall(glGenTextures(1, &tx->RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, tx->RendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tx->Width, tx->Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tx->LocalBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (tx->LocalBuffer != NULL){
        stbi_image_free(tx->LocalBuffer);

    }

};

void TX_Destruct(Texture* tx){
    GLCall(glDeleteTextures(1, &tx->RendererID))

};


void TX_Bind(unsigned int slot, Texture* tx){
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, tx->RendererID));

};


void TX_Unbind(){
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

};
