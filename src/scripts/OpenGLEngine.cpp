#include "OpenGLEngine.hpp"

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] =
    { //     COORDINATES     //
        -0.1f, -0.1f, 0.1f,
        -0.1f, -0.1f, -0.1f,
        0.1f, -0.1f, -0.1f,
        0.1f, -0.1f, 0.1f,
        -0.1f, 0.1f, 0.1f,
        -0.1f, 0.1f, -0.1f,
        0.1f, 0.1f, -0.1f,
        0.1f, 0.1f, 0.1f};

GLuint lightIndices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7};

OpenGLEngine::OpenGLEngine()
{
    Init();
    CreateWindow();
    gladLoadGL();
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    InitVertexArrays();

    InitSceneObjects();

    texure = new Texture("Textures/brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texure->texUnit(shaderProgram, "tex0", 0);


    camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));
    glEnable(GL_DEPTH_TEST);
}

OpenGLEngine::~OpenGLEngine()
{
    VAOGeneral->Delete();
    VBOGeneral->Delete();
    EBOGeneral->Delete();
    shaderProgram->Delete();
    texure->Delete();

    delete (VAOGeneral);
    delete (VBOGeneral);
    delete (EBOGeneral);
    delete (lightVAO);
    delete (lightVBO);
    delete (lightEBO);
    delete (shaderProgram);
    delete (lightShader);

    delete (camera);
    delete (texure);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void OpenGLEngine::Start()
{
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->Inputs(window);
        camera->UpdateMatrix(45.0f, 0.1f, 100.0f);

        shaderProgram->Activate();
        
        glUniform3f(shaderProgram->GetUniform("camPos"), camera->Position.x, camera->Position.y, camera->Position.z);

		camera->Matrix(shaderProgram, "camMatrix");
        texure->Bind();
        VAOGeneral->Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		lightShader->Activate();
        camera->Matrix(lightShader, "camMatrix");

		lightVAO->Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

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
    shaderProgram = new Shader("default.vert", "default.frag");
    VAOGeneral = new VAO();
    VAOGeneral->Bind();
    VBOGeneral = new VBO(vertices, sizeof(vertices));
    EBOGeneral = new EBO(indices, sizeof(indices));

    VAOGeneral->LinkAttribut(VBOGeneral, 0, 3, GL_FLOAT, 11* sizeof(float), (void *)0);
    VAOGeneral->LinkAttribut(VBOGeneral, 1, 3, GL_FLOAT, 11 * sizeof(float), (void *)(3 * sizeof(float)));
    VAOGeneral->LinkAttribut(VBOGeneral, 2, 3, GL_FLOAT, 11 * sizeof(float), (void *)(6 * sizeof(float)));
    VAOGeneral->LinkAttribut(VBOGeneral, 3, 3, GL_FLOAT, 11 * sizeof(float), (void *)(8 * sizeof(float)));
    VAOGeneral->Unbind();
    VBOGeneral->Unbind();
    EBOGeneral->Unbind();

    lightShader = new Shader("light.vert", "light.frag");
    lightVAO = new VAO();;
    lightVAO->Bind();

    lightVBO = new VBO(lightVertices, sizeof(lightVertices));
    lightEBO = new EBO(lightIndices, sizeof(lightIndices));

    lightVAO->LinkAttribut(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    lightVAO->Unbind();
    lightVBO->Unbind();
    lightEBO->Unbind();
}

void OpenGLEngine::InitSceneObjects()
{
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

    lightShader->Activate();
    glUniformMatrix4fv(lightShader->GetUniform("model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(lightShader->GetUniform("lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    shaderProgram->Activate();
    glUniformMatrix4fv(shaderProgram->GetUniform("model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(shaderProgram->GetUniform("lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(shaderProgram->GetUniform("lightPos"), lightPos.x, lightPos.y, lightPos.z);
}