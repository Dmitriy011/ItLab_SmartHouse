#pragma once

#include <SOIL.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Mesh.h"

#include <vector>

using namespace glm;
using namespace std;

class Model
{
public:
    vector<Texture> textures_loaded;                                                                     //список загруженных текстур

    Model(GLchar* cd);
    void Draw(Shader shader);

private:
    vector<Mesh> meshes;                                                                                 //вектор объектов типа Mesh
    string directory;

    void loadModel(string cd);                                                                           //загрузка модели в структуру объект сцены в терминологии Assimp
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
};
