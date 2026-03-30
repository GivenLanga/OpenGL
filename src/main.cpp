#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
/* #include "EBO.h" */
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cameraClass.h>

// Vertices coordinates for the cubeObject
// prettier-ignore
GLfloat vertices[] = {
    // positions          // texture coords   // normals
    // FRONT (+Z)
   -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,    1.0f, 0.0f,     0.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,    1.0f, 1.0f,     0.0f, 0.0f, 1.0f,

    0.5f,  0.5f,  0.5f,    1.0f, 1.0f,     0.0f, 0.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     0.0f, 0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f, 0.0f, 1.0f,

    // BACK (-Z)
   -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     0.0f, 0.0f, -1.0f,
   -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     0.0f, 0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f, 0.0f, -1.0f,

    0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f, 0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,    0.0f, 0.0f,     0.0f, 0.0f, -1.0f,
   -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     0.0f, 0.0f, -1.0f,

    // LEFT (-X)
   -0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    -1.0f, 0.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,    -1.0f, 0.0f, 0.0f,
   -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,    -1.0f, 0.0f, 0.0f,

   -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,    -1.0f, 0.0f, 0.0f,
   -0.5f, -0.5f,  0.5f,    1.0f, 0.0f,    -1.0f, 0.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    -1.0f, 0.0f, 0.0f,

    // RIGHT (+X)
    0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     1.0f, 0.0f, 0.0f,

    0.5f, -0.5f, -0.5f,    1.0f, 0.0f,     1.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     1.0f, 0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     1.0f, 0.0f, 0.0f,

    // TOP (+Y)
   -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     0.0f, 1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,    1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,    1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,     0.0f, 1.0f, 0.0f,

    // BOTTOM (-Y)
   -0.5f, -0.5f, -0.5f,    1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
   -0.5f, -0.5f,  0.5f,    1.0f, 0.0f,     0.0f, -1.0f, 0.0f,

    0.5f, -0.5f,  0.5f,    0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
   -0.5f, -0.5f, -0.5f,    1.0f, 1.0f,     0.0f, -1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     0.0f, -1.0f, 0.0f
};
GLuint indices[] = {
    0, 1, 3, // frist triangle
    3, 2, 1  // second triangle

};

// Vertices coordinates for the lightCube
GLfloat lightVertices[] = {
    -0.5f,
    -0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    -0.5f,
    0.5f,
    0.5f,
    -0.5f,
    0.5f,
    0.5f,
    -0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    -0.5f,
    -0.5f,
    -0.5f,

    -0.5f,
    -0.5f,
    0.5f,
    0.5f,
    -0.5f,
    0.5f,
    0.5f,
    0.5f,
    0.5f,
    0.5f,
    0.5f,
    0.5f,
    -0.5f,
    0.5f,
    0.5f,
    -0.5f,
    -0.5f,
    0.5f,

    -0.5f,
    0.5f,
    0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    -0.5f,
    -0.5f,
    -0.5f,
    -0.5f,
    -0.5f,
    -0.5f,
    -0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    0.5f,
    0.5f,

    0.5f,
    0.5f,
    0.5f,
    0.5f,
    0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    0.5f,
    0.5f,
    0.5f,
    0.5f,

    -0.5f,
    -0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    0.5f,
    0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    -0.5f,
    0.5f,
    -0.5f,
    -0.5f,
    -0.5f,

    -0.5f,
    0.5f,
    -0.5f,
    0.5f,
    0.5f,
    -0.5f,
    0.5f,
    0.5f,
    0.5f,
    0.5f,
    0.5f,
    0.5f,
    -0.5f,
    0.5f,
    0.5f,
    -0.5f,
    0.5f,
    -0.5f,
};

int w_width = 800;
int w_height = 800;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// lighting
glm::vec3 lightPos(1.0f, 1.0f, 2.0f);

// positions all containers
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(2.0f, 5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)};
// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f, 0.2f, 2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f, 2.0f, -12.0f),
    glm::vec3(0.0f, 0.0f, -3.0f)};

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
    VAO VAO1;
    VAO1.Bind();
    VBO VBO1(vertices, sizeof(vertices));
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 8* sizeof(float), (void *)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 8* sizeof(float), (void *)(5 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();

    Shader lightShader("resources/shaders/lightCube.vs", "resources/shaders/lightCube.fs");
    VAO lightVAO;
    lightVAO.Bind();
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
    lightVAO.Unbind();
    lightVBO.Unbind();

    unsigned int texture, texture2;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width_t, height_t, nrChannels;
    stbi_set_flip_vertically_on_load(true); // This will allow stbi and openGL to load the image in the same direction and not have it upsidedown
    unsigned char *data = stbi_load("resources/images/container2.png", &width_t, &height_t, &nrChannels, 0);
    if (data)
    {

        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width_t, height_t, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("resources/images/container2_specular.png", &width_t, &height_t, &nrChannels, 0);
    if (data)
    {

        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width_t, height_t, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glEnable(GL_DEPTH_TEST);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    camera.lastX = w_width / 2;
    camera.lastY = w_height / 2;

    cubeShader.Activate();
    int modelLoc = glGetUniformLocation(cubeShader.ID, "model");
    int viewLoc = glGetUniformLocation(cubeShader.ID, "view");
    int projLoc = glGetUniformLocation(cubeShader.ID, "proj");
    int lightColorLoc = glGetUniformLocation(cubeShader.ID, "lightColor");
    int viewPosLoc = glGetUniformLocation(cubeShader.ID, "viewPos");

    //Material Properties;
    int materialShinLoc = glGetUniformLocation(cubeShader.ID, "material.shininess");
    float  materialShininess = 64.0f;
    unsigned int diffuseMap = glGetUniformLocation(cubeShader.ID, "material.diffuse");
    unsigned int specularMap = glGetUniformLocation(cubeShader.ID, "material.specular");

    //Directional light
    int lightDirectionLoc_d = glGetUniformLocation(cubeShader.ID, "dirLight.direction");
    int lightAmbientLoc_d = glGetUniformLocation(cubeShader.ID, "dirLight.ambient");
    int lightDiffuseLoc_d = glGetUniformLocation(cubeShader.ID, "dirLight.diffuse");
    int lightSpecularLoc_d = glGetUniformLocation(cubeShader.ID, "dirLight.specular");
    glm::vec3 lightDirection_d = glm::vec3(-0.2f, -1.0f, -0.3f);
    glm::vec3 lightAmbient_d = glm::vec3(0.1f);
    glm::vec3 lightDiffuse_d = glm::vec3(0.6f);
    glm::vec3 lightSpecular_d = glm::vec3(0.5f);
    
    // Share'd by all point lights
    float lightConstant_p = 1.0f;
    float lightLinear_p = 0.09f;
    float lightQuadratic_p = 0.032f;
    glm::vec3 lightAmbient_p = glm::vec3(0.05f);
    glm::vec3 lightDiffuse_p = glm::vec3(0.8f);
    glm::vec3 lightSpecular_p = glm::vec3(1.0f);

    //Point Lights 
    std::vector <int> lightPositionLoc_p(4), lightAmbientLoc_p(4), lightDiffuseLoc_p(4), lightSpecularLoc_p(4);
    std::vector <int> lightConstantLoc_p(4), lightLinearLoc_p(4), lightQuadraticLoc_p(4);

    for (int i = 0; i < 4; i++){

        std::string idx = std::to_string(i);

        lightPositionLoc_p[i] = glGetUniformLocation(cubeShader.ID, ("pointLights[" + idx + "].position").c_str());
        lightAmbientLoc_p[i] = glGetUniformLocation(cubeShader.ID, ("pointLights[" + idx + "].ambient").c_str());
        lightDiffuseLoc_p[i] = glGetUniformLocation(cubeShader.ID, ("pointLights[" + idx + "].diffuse").c_str());
        lightSpecularLoc_p[i] = glGetUniformLocation(cubeShader.ID, ("pointLights[" + idx + "].specular").c_str());

        lightConstantLoc_p[i] = glGetUniformLocation(cubeShader.ID, ("pointLights[" + idx + "].constant").c_str());
        lightLinearLoc_p[i] = glGetUniformLocation(cubeShader.ID, ("pointLights[" + idx + "].linear").c_str());
        lightQuadraticLoc_p[i] = glGetUniformLocation(cubeShader.ID, ("pointLights[" + idx + "].quadratic").c_str());
    }

    //SpotLight
    int lightPositionLoc_s = glGetUniformLocation(cubeShader.ID, "spotLight.position");
    int lightDirectionLoc_s = glGetUniformLocation(cubeShader.ID, "spotLight.direction");
    int lightAmbientLoc_s = glGetUniformLocation(cubeShader.ID, "spotLight.ambient");
    int lightDiffuseLoc_s = glGetUniformLocation(cubeShader.ID, "spotLight.diffuse");
    int lightConstantLoc_s = glGetUniformLocation(cubeShader.ID, "spotLight.constant");
    int lightLinearLoc_s = glGetUniformLocation(cubeShader.ID, "spotLight.linear");
    int lightQuadraticLoc_s = glGetUniformLocation(cubeShader.ID, "spotLight.quadratic");
    int lightSpecularLoc_s = glGetUniformLocation(cubeShader.ID, "spotLight.specular");
    int lightRadiusLoc_s = glGetUniformLocation(cubeShader.ID, "spotLight.radius");
    int lightOuterRadiusLoc_s = glGetUniformLocation(cubeShader.ID, "spotLight.outerRadius");
    glm::vec3 lightAmbient_s = glm::vec3(0.0f);
    glm::vec3 lightDiffuse_s = glm::vec3(1.0f);
    glm::vec3 lightSpecular_s = glm::vec3(1.0f);
    float lightRadius_s = glm::cos(glm::radians(12.5f));
    float lightOuterRadius_s = glm::cos(glm::radians(17.5f));


    //Light cube
    lightShader.Activate(); 
    int modelLocLight = glGetUniformLocation(lightShader.ID, "model");
    int viewLocLight = glGetUniformLocation(lightShader.ID, "view");
    int projLocLight = glGetUniformLocation(lightShader.ID, "proj");

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

       /*  glm::mat4 model = glm::mat4(1.0f); */
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);
        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
       /*  model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.1f)); */
        view = camera.getViewMatrix();
        proj = glm::perspective(glm::radians(camera.fov), (float)w_width / (float)w_height, 0.1f, 100.0f);
        /* lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;  */
 
        // Cube
        cubeShader.Activate();
       /*  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); */
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
        glUniform3fv(viewPosLoc, 1, glm::value_ptr(camera.cameraPos));

        glUniform1i(diffuseMap, 0);
        glUniform1i(specularMap, 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture); // diffuse
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2); // specular

        // Material properties
        glUniform1f(materialShinLoc, materialShininess);

        // Directional Light properties
        glUniform3fv(lightDirectionLoc_d,1, glm::value_ptr(lightDirection_d));
        glUniform3fv(lightAmbientLoc_d, 1, glm::value_ptr(lightAmbient_d));
        glUniform3fv(lightDiffuseLoc_d, 1, glm::value_ptr(lightDiffuse_d));
        glUniform3fv(lightSpecularLoc_d, 1, glm::value_ptr(lightSpecular_d));

        //Point lights

        for(int i = 0; i < 4; i ++ ){

            glUniform3fv(lightPositionLoc_p[i], 1, glm::value_ptr(pointLightPositions[i]));
            glUniform3fv(lightAmbientLoc_p[i], 1, glm::value_ptr(lightAmbient_p));
            glUniform3fv(lightDiffuseLoc_p[i], 1, glm::value_ptr(lightDiffuse_p));
            glUniform3fv(lightSpecularLoc_p[i], 1, glm::value_ptr(lightSpecular_p));

            glUniform1f(lightConstantLoc_p[i], lightConstant_p);
            glUniform1f(lightLinearLoc_p[i], lightLinear_p);
            glUniform1f(lightQuadraticLoc_p[i], lightQuadratic_p);
        }
          
        //Spot Lights
        glUniform3fv(lightPositionLoc_s, 1, glm::value_ptr(camera.cameraPos));
        glUniform3fv(lightDirectionLoc_s, 1, glm::value_ptr(camera.cameraFront));
        glUniform3fv(lightAmbientLoc_s, 1, glm::value_ptr(lightAmbient_s));
        glUniform3fv(lightDiffuseLoc_s, 1, glm::value_ptr(lightDiffuse_s));
        glUniform3fv(lightSpecularLoc_s, 1, glm::value_ptr(lightSpecular_s));
        glUniform1f(lightConstantLoc_s, lightConstant_p);
        glUniform1f(lightLinearLoc_s, lightLinear_p);
        glUniform1f(lightQuadraticLoc_s, lightQuadratic_p);
        glUniform1f(lightRadiusLoc_s, lightRadius_s);
        glUniform1f(lightOuterRadiusLoc_s, lightOuterRadius_s);


        VAO1.Bind();

        for(unsigned int i =0; i< 10; i++){
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i + rotation;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Setup model matrix for light cube

        // Set uniforms AFTER activating the shader
        lightShader.Activate();

        glUniformMatrix4fv(viewLocLight, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLocLight, 1, GL_FALSE, glm::value_ptr(proj));

        // Bind the VAO and draw
        lightVAO.Bind();

        for (unsigned int i = 0; i < 4; i++)
        {
            glm::mat4 modelLight = glm::mat4(1.0f);
            modelLight = glm::translate(modelLight, pointLightPositions[i]); 
            modelLight = glm::scale(modelLight, glm::vec3(0.2f)); // Small cube
            glUniformMatrix4fv(modelLocLight, 1, GL_FALSE, glm::value_ptr(modelLight));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        lightVAO.Unbind();

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
    glDeleteTextures(1, &texture);
    VAO1.Delete();
    VBO1.Delete();
    cubeShader.Delete();

    lightVAO.Delete();
    lightVBO.Delete();
    lightShader.Delete();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
