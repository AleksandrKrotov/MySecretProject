#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include "glad.h"

class VertexBuffer
{
    public:
        GLuint ID;

        VertexBuffer(GLfloat* vertices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};
#endif