#include "shader.h"
#include "renderer.h"







void SH_Construct(Shader* shader, char* filepath){
    shader->filepath = filepath;
    shader->RendererID = 0;
    sh_new_arena(shader->UniformLocationCache);
    shdefault(shader->UniformLocationCache, -1);


    ShaderProgramSource source = SH_ParseShader(filepath);
    shader->RendererID = SH_CreateShader(source.VertexSource, source.FragmentSource);


};


void SH_Destruct(Shader* shader){

    GLCall(glDeleteProgram(shader->RendererID));


};



void SH_Bind(Shader* shader){

    GLCall(glUseProgram(shader->RendererID));

};


void SH_Unbind(){

    GLCall(glUseProgram(0));

};

void SH_SetUniform1i(Shader* shader, char* name, int value){
    SH_Bind(shader);
    GLCall(glUniform1i(SH_GetUniformLocation(shader, name), value));

};

void SH_SetUniform1iv(Shader* shader, char* name, unsigned int count, int value[]){
    SH_Bind(shader);
    GLCall(glUniform1iv(SH_GetUniformLocation(shader, name), count, value));

};

void SH_SetUniform1f(Shader* shader, char* name, float value){
    SH_Bind(shader);
    GLCall(glUniform1f(SH_GetUniformLocation(shader, name), value));

};

void SH_SetUniformMat4f(Shader* shader, char* name, mat4 matrix){
    SH_Bind(shader);
    GLCall(glUniformMatrix4fv(SH_GetUniformLocation(shader, name), 1, GL_FALSE, &matrix[0][0]));

};

void SH_SetUniform4f(Shader* shader, char* name, float v0, float v1, float v2, float v3){
    SH_Bind(shader);
    GLCall(glUniform4f(SH_GetUniformLocation(shader, name), v0, v1, v2, v3));

};

int SH_GetUniformLocation(Shader* shader, char* name){

    if (shget(shader->UniformLocationCache, name) != -1){
        return shget(shader->UniformLocationCache, name);
    }

    GLCall(int location = glGetUniformLocation(shader->RendererID, name));
    if (location == -1){
        printf("Warning: Uniform %s doesn't exist\n", name);
    }

    shput(shader->UniformLocationCache, name, location);
    return location;
};


unsigned int SH_CreateShader(const char* vertexShader, const char* fragmentShader){

    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = SH_CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = SH_CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

unsigned int SH_CompileShader(unsigned int type, const char* source){

    GLCall(unsigned int id = glCreateShader(type));
    GLCall(glShaderSource(id, 1, &source, NULL));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE){
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        if (type == GL_VERTEX_SHADER){
            printf("Failed to compile vertex shader!\n");
        } else {
            printf("Failed to compile fragment shader!\n");
        }
        printf("%s\n", message);
        GLCall(glDeleteShader(id));
        return 0;

    }

    return id;
}

ShaderProgramSource SH_ParseShader(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("Could not open file: %s\n", filepath);
        exit(1);
    }

    ShaderProgramSource source;
    source.VertexSource = NULL;
    source.FragmentSource = NULL;

    ShaderType type = NONE;
    char buffer[BUFFER_SIZE];
    char* vertexShader = NULL;
    char* fragmentShader = NULL;
    size_t vertexSize = 0;
    size_t fragmentSize = 0;

    while (fgets(buffer, BUFFER_SIZE, file)) {
        size_t len = strlen(buffer);
        

        if (strstr(buffer, "#shader") != NULL) {
            if (strstr(buffer, "vertex") != NULL) {
                type = VERTEX;
            } else if (strstr(buffer, "fragment") != NULL) {
                type = FRAGMENT;
            }
        } else {
            if (type == VERTEX) {
                vertexShader = realloc(vertexShader, vertexSize + len + 1);
                if (!vertexShader) {
                    printf("Memory allocation failed\n");
                    exit(1);
                }
                strcpy(vertexShader + vertexSize, buffer);
                vertexSize += len;
            } else if (type == FRAGMENT) {
                fragmentShader = realloc(fragmentShader, fragmentSize + len + 1);
                if (!fragmentShader) {
                    printf("Memory allocation failed\n");
                    exit(1);
                }
                strcpy(fragmentShader + fragmentSize, buffer);
                fragmentSize += len;
            }
        }
    }

    fclose(file);

    // Ensure the buffers are null-terminated
    if (vertexShader) {
        vertexShader[vertexSize] = '\0';
    }
    if (fragmentShader) {
        fragmentShader[fragmentSize] = '\0';
    }

    source.VertexSource = vertexShader;
    source.FragmentSource = fragmentShader;

    return source;
}