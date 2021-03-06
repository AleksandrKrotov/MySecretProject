#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
    public:
        GLuint ID;
        Shader(const char *vertexFile, const char* fragmentFile);

        void Activate();
        void Delete();
        GLuint GetUniform(const char* param);

    private:
        const char* vertexSource;
        const char* fragmentSource;

        void InitShaderProgram();
        void AttachShader(GLuint shaderType, const char* shaderSource, const char* shaderTypeName);
        void compileErrors(unsigned int shader, const char* type);
};

#endif