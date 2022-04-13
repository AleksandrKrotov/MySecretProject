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

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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
        void InitShaderProgram();
        void InitShader(GLuint shaderType, const char* shaderSource);
        void InitVertexArrays();
};

#endif