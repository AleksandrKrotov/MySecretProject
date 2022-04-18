#include <iostream>
#include "IEngine.hpp"
#include "OpenGLEngine.hpp"


int main(int argc, char *argv[])
{
    IEngine *engine = new OpenGLEngine();

    engine->Start();

    delete(engine);
    return 0;
};