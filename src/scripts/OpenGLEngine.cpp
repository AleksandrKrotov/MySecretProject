#include "OpenGLEngine.h"

    // Vertices coordinates
    GLfloat vertices[] =
    { //               COORDINATES                  /     COLORS           //
        -0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,    0.8f, 0.3f,  0.02f, // Lower left corner
        0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
        0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
        -0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,    0.9f, 0.45f, 0.17f, // Inner left
        0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
        0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Lower right triangle
        5, 4, 1 // Upper triangle
    };

OpenGLEngine::OpenGLEngine()
{
    Init();
    CreateWindow();
    gladLoadGL();
    glViewport(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
    shaderProgram = new Shader("default.vert", "default.frag");
    scaleParam = shaderProgram->GetUniform("scale");
    InitVertexArrays();
}

OpenGLEngine::~OpenGLEngine()
{
    vertexArray->Delete();
    vertexBuffer->Delete();
    elementBuffer->Delete();
    shaderProgram->Delete();

    delete(vertexArray);
    delete(vertexBuffer);
    delete(elementBuffer);
    delete(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void OpenGLEngine::Start()
{
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram->Activate();
        glUniform1f(scaleParam, 0.7f);
        vertexArray->Bind();
        
        glDrawElements(GL_TRIANGLES, 9,GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

int OpenGLEngine::Init()
{
    if (!glfwInit())
    {
        std::cout << "Failed to init GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    return 0;
}

int OpenGLEngine::CreateWindow()
{
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MySecretProject", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    return 0;
}

void OpenGLEngine::InitVertexArrays()
{
    vertexArray = new VertexArray();
    vertexArray->Bind();
    vertexBuffer = new VertexBuffer(vertices, sizeof(vertices));
    elementBuffer = new ElementBuffer(indices, sizeof(indices));

    vertexArray->LinkAttribut(*vertexBuffer, 0,  3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vertexArray->LinkAttribut(*vertexBuffer, 1,  3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    vertexArray->Unbind();
    vertexBuffer->Unbind();
    elementBuffer->Unbind();
}