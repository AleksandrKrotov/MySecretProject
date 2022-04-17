#ifndef OPENGLENGINE_HPP
#define OPENGLENGINE_HPP

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include "glad.h"
#include <GLFW/glfw3.h>
#endif

#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include "stb_image.h"

#include "IEngine.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"


class OpenGLEngine : public IEngine
{
    private:
        GLFWwindow*     window;
        GLuint          VAO, VBO, EBO;
        Shader*         shaderProgram;
        Camera*         camera;
        VertexArray*    vertexArray;
        VertexBuffer*   vertexBuffer;
        ElementBuffer*  elementBuffer;
        GLuint          tex0Uni;
        Texture*        texure;

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