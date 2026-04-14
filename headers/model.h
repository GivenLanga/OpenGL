#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"

class Model{
    
       std:: vector <Mesh> meshes;
       std:: vector <Texture> textures_loaded;
       std:: string directory;
       bool gammaCorrecton;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector <Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);


    public:

        Model(std::string const &path, bool gamma = false)
        :gammaCorrecton{gamma}
        {
            loadModel(path);
        }
        void Draw(Shader &shader);

};


