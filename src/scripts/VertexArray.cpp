#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

void VertexArray::LinkAttribut(VertexBuffer &vertexBuffer, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    vertexBuffer.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vertexBuffer.Unbind();
}

void VertexArray::Bind()
{
    glBindVertexArray(ID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::Delete()
{
    glDeleteVertexArrays(1, &ID);
}