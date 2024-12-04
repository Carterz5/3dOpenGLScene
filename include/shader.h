#ifndef SHADER_H
#define SHADER_H
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "cglm/cglm.h"
#include "cglm/mat4.h"

typedef struct Shader {
    char* filepath;
    unsigned int RendererID;
    struct {char* key; int value;} *UniformLocationCache;

} Shader;

#define BUFFER_SIZE 1024

typedef struct {
    char* VertexSource;
    char* FragmentSource;
} ShaderProgramSource;

typedef enum {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
} ShaderType;


void SH_Construct(Shader* shader, char* filepath);
void SH_Destruct(Shader* shader);
void SH_Bind(Shader* shader);
void SH_Unbind();
void SH_SetUniform1i(Shader* shader, char* name, int value);
void SH_SetUniform1iv(Shader* shader, char* name, unsigned int count, int value[]);
void SH_SetUniform1f(Shader* shader, char* name, float value);
void SH_SetUniformMat4f(Shader* shader, char* name, mat4 matrix);
void SH_SetUniform4f(Shader* shader, char* name, float v0, float v1, float v2, float v3);
int SH_GetUniformLocation(Shader* shader, char* name);
unsigned int SH_CreateShader(const char* vertexShader, const char* fragmentShader);
unsigned int SH_CompileShader(unsigned int type, const char* source);
ShaderProgramSource SH_ParseShader(const char* filepath);

#endif