#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "glad.h"
#include "VertexBuffer.hpp"

class VertexArray
{
    public:
        GLuint ID;

        VertexArray();

        void LinkVertexBuffer(VertexBuffer &vertexBuffer, GLuint layout);

        void Bind();
        void Unbind();
        void Delete();
};

#endif