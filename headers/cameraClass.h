#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{

public:
    glm::vec3 cameraPos{};
    glm::vec3 cameraFront{};
    glm::vec3 cameraUp{};
    float lastX;
    float lastY;
    bool firstTime = true;
    float yaw = -90;
    float pitch = 0;
    float fov = 45.0;

    Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);

    static void mouse_callback_wrapper(GLFWwindow *window, double xpos, double ypos);
    static void scroll_callback_wrapper(GLFWwindow *window, double xoffset, double yoffset);

    void mouse_callback(GLFWwindow *window, double xPos, double yPos);
    void processInput(GLFWwindow *window, float deltaTime);
    void scroll_callback(GLFWwindow *window, double xOffset, double yOffet);
    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }
};