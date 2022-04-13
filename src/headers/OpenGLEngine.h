#ifndef OPENGLENGINE_H
#define OPENGLENGINE_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include "glad.h"
#include <GLFW/glfw3.h>
#endif

#include <iostream>
#include <math.h>
#include "stb_image.h"

#include "IEngine.h"
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
        GLuint scaleParam, tex0Uni;
        GLuint texture;

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