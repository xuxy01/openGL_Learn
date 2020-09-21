#pragma once
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "lib/std_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"
#include "Render.h"
#include "Utils.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

class ModelObject
{
public:
    ModelObject()
    {
    }
    /*  函数   */
    ModelObject(const char* path)
    {
        loadModel(path);
    }
    void Draw(Shader& shader, glm::mat4 transform);
private:
    /*  模型数据  */
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    /*  函数   */
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};