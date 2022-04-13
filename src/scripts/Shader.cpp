#include "Shader.hpp"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);
    std::cout << "vertexCode: \n" << vertexCode <<std::endl;
    std::cout << "fragmentCode: \n" << fragmentCode <<std::endl;


    vertexSource = vertexCode.c_str();
    fragmentSource = fragmentCode.c_str();

    InitShaderProgram();
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}

void Shader::InitShaderProgram()
{
    ID = glCreateProgram();
    AttachShader(GL_VERTEX_SHADER, vertexSource);
    AttachShader(GL_FRAGMENT_SHADER, fragmentSource);
    glLinkProgram(ID);
}

void Shader::AttachShader(GLuint shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    glAttachShader(ID, shader);
    glDeleteShader(shader);
}

std::string get_file_contents(const char* filename)
{
    std::string fullPath = std::string("Shaders/") + std::string(filename);

    std::ifstream in(fullPath.c_str(), std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }

    std::cout << "Can't load file wit path: " << fullPath << std::endl;
    throw(errno);
}