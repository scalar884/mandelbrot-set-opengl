#include "shader.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int program;
static unsigned int VAO;

/* load shader from file */
char* loadShaderSource(const char* path) {
    FILE* file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* source = malloc(length + 1);
    fread(source, 1, length, file);
    source[length] = '\0';
    fclose(file);
    return source;
}

/* compile shader */
unsigned int compileShader(GLenum type, const char* source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    return shader;
}

/* init shaders and buffers */
void shaderInit() {
    /* load shaders from files */
    char* vertexSource = loadShaderSource("shaders/vertex.shader");
    char* fragmentSource = loadShaderSource("shaders/fragment.shader");
    
    /* compile shaders */
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
    
    /* create program */
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    
    /* cleanup */
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    free(vertexSource);
    free(fragmentSource);
    
    /* fullscreen quad */
    float vertices[] = {
        -1.0f, -1.0f,  1.0f, -1.0f,  -1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f, -1.0f,   1.0f, 1.0f
    };
    
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

/* render frame */
void shaderRender() {
    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
