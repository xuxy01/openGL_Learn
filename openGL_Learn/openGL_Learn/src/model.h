#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "lib/std_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Model
{
public:
    /*  ����   */
    Model(char* path)
    {
        loadModel(path);
    }
    void Draw(Shader shader);
private:
    /*  ģ������  */
    vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    /*  ����   */
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        string typeName);
};