#ifndef ELEMENTBUFFER_HPP
#define ELEMENTBUFFER_HPP

#include "glad.h"

class ElementBuffer
{
    public:
        GLuint ID;

        ElementBuffer(GLuint *indices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};
#endif