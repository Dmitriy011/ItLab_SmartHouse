#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

using namespace std;

struct Vertex                                                                           //Для хранения каждой вершины
{
    glm::vec3 Position;                                                                 //Вектор позиций для каждой вершины
    glm::vec3 Normal;                                                                   //Векто нормали для каждой врешины
    glm::vec2 TexCoords;                                                                //Текстурные координаты каждой вершины
};

struct Texture                                                                          //Хранит текстурные данные для каждой вершины
{
    unsigned int id;                            
    string type;                                                                        //тип текстуры(диффузная или бликовая)
};

class Mesh 
{
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    void Draw(Shader& shader);
private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();                                                                       //Инициализируем буферы
};