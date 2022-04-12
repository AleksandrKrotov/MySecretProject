#ifndef OPENGLENGINE_H
#define OPENGLENGINE_H

#include "IEngine.h"
#include <GLFW/glfw3.h>
#include <iostream>

class OpenGLEngine : public IEngine
{
    public:

    private:
        void Init();

    public:
        OpenGLEngine();
        ~OpenGLEngine();
        void Start();
};
#endif