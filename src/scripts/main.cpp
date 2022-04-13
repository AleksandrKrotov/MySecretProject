#include <iostream>
#include "SDLEngine.h"
#include "IEngine.h"
#include "OpenGLEngine.h"


int main(int argc, char *argv[])
{
    IEngine *engine = new OpenGLEngine();

    engine->Start();

    delete(engine);
    return 0;
};