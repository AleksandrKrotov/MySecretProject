#include "OpenGLEngine.h"

OpenGLEngine::OpenGLEngine()
{
    Init();
}

OpenGLEngine::~OpenGLEngine()
{

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
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

// int SDLEngine::CreateWindow()
// {
// }

// int SDLEngine::CreateRenderer()
// {
// }

// int SDLEngine::CreateSurface(const char* path)
// {
// }

// int SDLEngine::CreateTexture()
// {

// }