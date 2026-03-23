#include <cameraClass.h>

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
    : cameraPos{cameraPos}, cameraFront{cameraFront}, cameraUp{cameraUp}
{
}

void Camera::processInput(GLFWwindow *window, float deltaTime)
{
    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::mouse_callback(GLFWwindow *window, double xPos, double yPos)
{
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
        return;
    if (firstTime)
    {
        lastX = xPos;
        lastY = yPos;
        firstTime = false;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    const float sensitivity = 0.01f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
    fov -= (float)yOffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void Camera::mouse_callback_wrapper(GLFWwindow *window, double xpos, double ypos)
{
    Camera *cam = static_cast<Camera *>(glfwGetWindowUserPointer(window));
    cam->mouse_callback(window, xpos, ypos);
}

void Camera::scroll_callback_wrapper(GLFWwindow *window, double xoffset, double yoffset)
{
    Camera *cam = static_cast<Camera *>(glfwGetWindowUserPointer(window));
    cam->scroll_callback(window, xoffset, yoffset);
}