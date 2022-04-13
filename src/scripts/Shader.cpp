#include "Shader.hpp"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

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

GLuint Shader::GetUniform(const char* paramName)
{
    return glGetUniformLocation(ID, paramName);
}

void Shader::InitShaderProgram()
{
    ID = glCreateProgram();
    AttachShader(GL_VERTEX_SHADER, vertexSource, "VERTEX");
    AttachShader(GL_FRAGMENT_SHADER, fragmentSource, "FRAGMENT");
    glLinkProgram(ID);
}

void Shader::AttachShader(GLuint shaderType, const char* shaderSource, const char* shaderTypeName)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    compileErrors(shader, shaderTypeName);
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

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (std::strcmp(type, "PROGRAM") != 0)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}