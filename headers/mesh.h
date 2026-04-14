#pragma once

#include<iostream>
#include<string>
#include<vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"

#define MAX_BONE_INFLUENCE 4
struct Vertex {
    glm::vec3 Postion;
    glm::vec3 Normal;
    glm::vec2 TexCoords;   
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
        int m_BoneIDs[MAX_BONE_INFLUENCE];
        float m_weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};


class Mesh {

    unsigned int VBO, EBO;
    void setUpMesh();

 public:
    
   std::vector<Vertex> vertices;
   std::vector<unsigned int> indices;
   std::vector<Texture> textures;
   unsigned int VAO;

   Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
   void Draw (Shader &shader);

};