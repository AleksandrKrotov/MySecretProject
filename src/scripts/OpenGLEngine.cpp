#include "OpenGLEngine.hpp"

    // Vertices coordinates
    GLfloat vertices[] =
    { //      COORDINATES   /     COLORS         // TexCoord //
        -0.5f, 0.0f,  0.5f,     1.f, 0.0f, 00.0f,	0.0f, 0.0f,
        -0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 1.0f,	5.0f, 0.0f,
        0.5f, 0.0f, -0.5f,      1.0f, 0.0f, 0.0f,	    .0f, 0.0f,
        0.5f, 0.0f,  0.5f,      0.0f, 0.0f, 1.0f,	    5.0f, 0.0f,
        0.0f, 0.8f,  0.0f,      0.0f, 1.0f, 0.0f,	    2.5f, 5.0f
    };

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

OpenGLEngine::OpenGLEngine()
{
    Init();
    CreateWindow();
    gladLoadGL();
    glViewport(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
    shaderProgram = new Shader("default.vert", "default.frag");
    InitVertexArrays();

    texure = new Texture("Textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    texure->texUnit(shaderProgram, "tex0", 0);

    camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f), shaderProgram->GetUniform("camMatrix"));
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
    delete(camera);
    delete(texure);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void OpenGLEngine::Start()
{
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram->Activate();

        camera->Inputs(window);
        camera->Matrix(45.0f, 0.1f, 100.0f);

        texure->Bind();

        vertexArray->Bind();
        
        glDrawElements(GL_TRIANGLES, sizeof(indices)/ sizeof(int),GL_UNSIGNED_INT, 0);

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