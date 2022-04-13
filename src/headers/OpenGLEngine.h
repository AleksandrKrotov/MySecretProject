#ifndef OPENGLENGINE_H
#define OPENGLENGINE_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include "glad.h"
#include <GLFW/glfw3.h>
#endif

#include "IEngine.h"
#include <iostream>
#include <math.h>
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"


class OpenGLEngine : public IEngine
{
    private:
        GLFWwindow *window;
        GLuint VAO, VBO, EBO;
        Shader *shaderProgram;
        VertexArray *vertexArray;
        VertexBuffer *vertexBuffer;
        ElementBuffer *elementBuffer;

    public:
        OpenGLEngine();
        ~OpenGLEngine();
        void Start();

    private:
        int Init();
        int CreateWindow();
        void InitVertexArrays();
};

#endif