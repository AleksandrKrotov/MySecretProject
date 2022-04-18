#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include "glad.h"

class VBO
{
    public:
        GLuint ID;

        VBO(GLfloat* vertices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};
#endif