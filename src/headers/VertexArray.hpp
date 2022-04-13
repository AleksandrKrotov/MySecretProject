#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "glad.h"
#include "VertexBuffer.hpp"

class VertexArray
{
    public:
        GLuint ID;

        VertexArray();

        void LinkAttribut(VertexBuffer &vertexBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

        void Bind();
        void Unbind();
        void Delete();
};

#endif