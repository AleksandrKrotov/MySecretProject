#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "glad.h"
#include "stb_image.h"

#include "Shader.hpp"

class Texture
{
    public:
        GLuint ID;
        GLenum type;
        GLenum unit;

        Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

        void texUnit(Shader* shader, const char* uniform, GLuint unit);
        
        void Bind();

        void Unbind();

        void Delete();

};

#endif