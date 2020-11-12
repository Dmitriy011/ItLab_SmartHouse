#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"

using namespace std;

struct Vertex                                                                           //Для хранения каждой вершины полигональной сетки
{
    glm::vec3 Position;                                                                 //Вектор позиций для каждой вершины
    glm::vec3 Normal;                                                                   //Векто нормали для каждой врешины
    glm::vec2 TexCoords;                                                                //Текстурные координаты каждой вершины
};

struct Texture                                                                          //Хранит текстурные данные для каждой вершины
{
    GLuint id;                            
    string type;                                                                        //тип текстуры(диффузная или бликовая)
    aiString path;                                                                      //путь к текстуре
};

class Mesh                                                                              //Полигональная сетка
{
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

    void Draw(Shader& shader);                                                          //отрисовыв. полигональной сетки
private:
    GLuint VAO, VBO, EBO;

    void setupMesh();                                                                   //Инициализируем буферы
};