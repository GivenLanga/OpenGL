#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <filesystem>
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cameraClass.h>
#include <assimp/version.h>
#include "model.h"


int w_width = 800;
int w_height = 800;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);



int main()
{
 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 800, "ISUCK", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    gladLoadGL();
    glViewport(0, 0, w_width, w_height);

    Camera camera{cameraPos, cameraFront, cameraUp};
    glfwSetWindowUserPointer(window, &camera);
    glfwSetCursorPosCallback(window, Camera::mouse_callback_wrapper);
    glfwSetScrollCallback(window, Camera::scroll_callback_wrapper);

    // IMGUI SETUP
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    //..............................................

    Shader cubeShader("resources/shaders/default.vs", "resources/shaders/default.fs");

    //Load models
    stbi_set_flip_vertically_on_load(true);
    Model ourModel (std::filesystem::path( "resources/backpack/backpack.obj"));
   
  
    glEnable(GL_DEPTH_TEST);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    camera.lastX = w_width / 2;
    camera.lastY = w_height / 2;

    cubeShader.Activate();
    int modelLoc = glGetUniformLocation(cubeShader.ID, "model");
    int projLoc = glGetUniformLocation(cubeShader.ID, "projection");
    int viewLoc = glGetUniformLocation(cubeShader.ID, "view");

    bool cursorEnabled = true;
    bool tabPressedLastFrame = false;
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        camera.processInput(window, deltaTime);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        bool tabPressedNow = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;

        if (tabPressedNow && !tabPressedLastFrame)
        {
            cursorEnabled = !cursorEnabled;

            if (cursorEnabled)
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            else
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        tabPressedLastFrame = tabPressedNow;

        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1.0 / 60.0)
        {
            rotation += 1.0f;
            prevTime = crntTime;
        }
        cubeShader.Activate();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);
        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

        model = glm::rotate(model,
                            glm::radians(rotation),
                            glm::vec3(0.0f, 1.0f, 0.0f));

        model = glm::scale(model, glm::vec3(1.0f));
        view = camera.getViewMatrix();
        proj = glm::perspective(glm::radians(camera.fov), (float)w_width / (float)w_height, 0.1f, 100.0f);

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        ourModel.Draw(cubeShader);

        
        // ImGui Window
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Control Center");
        ImGui::Text("OpenGL + ImGui working!");
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //................................................

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }
    // Delete all the objects we've created
    cubeShader.Delete();

 
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
