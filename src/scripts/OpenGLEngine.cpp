#include "OpenGLEngine.h"

OpenGLEngine::OpenGLEngine()
{
    Init();
}

OpenGLEngine::~OpenGLEngine()
{
    glfwTerminate();
}

void OpenGLEngine::Start()
{
}

// void SDLEngine::UpdateSurface()
// {

// }

void OpenGLEngine::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

int OpenGLEngine::CreateWindow()
{
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    return 0;
}

// int SDLEngine::CreateRenderer()
// {
// }

// int SDLEngine::CreateSurface(const char* path)
// {
// }

// int SDLEngine::CreateTexture()
// {

// }