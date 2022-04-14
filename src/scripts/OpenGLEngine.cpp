#include "OpenGLEngine.h"

    // Vertices coordinates
    GLfloat vertices[] =
    { //      COORDINATES   /     COLORS         //
        -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f, // Lower left corner
        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f, 0.0f,     0.0f, 1.0f, // Uper left corner
         0.5f,  0.5f, 0.0f,    0.0f, 0.0f, 1.0f,     1.0f, 1.0f, // Upper right corner
         0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,     1.0f, 0.0f // Lower right corner
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 2, 1, // Lower left triangle
        0, 3, 2, // Lower right triangle
    };

OpenGLEngine::OpenGLEngine()
{
    Init();
    CreateWindow();
    gladLoadGL();
    glViewport(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
    shaderProgram = new Shader("default.vert", "default.frag");
    InitVertexArrays();

    scaleParam = shaderProgram->GetUniform("scale");

    texure = new Texture("Textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    texure->texUnit(shaderProgram, "tex0", 0);
}

OpenGLEngine::~OpenGLEngine()
{
    vertexArray->Delete();
    vertexBuffer->Delete();
    elementBuffer->Delete();
    shaderProgram->Delete();
    texure->Delete();

    delete(vertexArray);
    delete(vertexBuffer);
    delete(elementBuffer);
    delete(shaderProgram);
    delete(texure);

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

        glUniform1f(scaleParam, 0.5f);

        texure->Bind();

        vertexArray->Bind();
        
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, 0);

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

    vertexArray->LinkAttribut(*vertexBuffer, 0,  3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vertexArray->LinkAttribut(*vertexBuffer, 1,  3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vertexArray->LinkAttribut(*vertexBuffer, 2,  2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vertexArray->Unbind();
    vertexBuffer->Unbind();
    elementBuffer->Unbind();
}