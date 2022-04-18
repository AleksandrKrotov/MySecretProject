#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.hpp"

class Camera
{
    private:
        bool firstClick = true;

        void KeyboardInteraction(GLFWwindow* window);
        void MouseInteraction(GLFWwindow* window);

    public:
        glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f,0.0f);
        glm::mat4 cameraMatrix = glm::mat4(1.0f);

        int width;
        int height;

        float speed = 0.1f;
        float sensitivety = 100.0f;

        Camera(int width, int height, glm::vec3 position);
        void Matrix(Shader* shader, const char* uniform);
        void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
        
        void Inputs(GLFWwindow *window);
};

#endif