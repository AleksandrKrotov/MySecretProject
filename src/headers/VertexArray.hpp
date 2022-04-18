#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "glad.h"
#include "VertexBuffer.hpp"

class VAO
{
    public:
        GLuint ID;

        VAO();

        void LinkAttribut(VBO *vertexBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

        void Bind();
        void Unbind();
        void Delete();
};

#endif