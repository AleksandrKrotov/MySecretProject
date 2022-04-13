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

class OpenGLEngine : public IEngine
{
    private:
        GLFWwindow *window;
        GLuint shaderProgram;
        GLuint VAO, VBO;

    public:
        OpenGLEngine();
        ~OpenGLEngine();
        void Start();

    private:
        int Init();
        int CreateWindow();
        void InitShaders();
};

#endif