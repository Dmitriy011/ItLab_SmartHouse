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

struct Vertex                                                                           //��� �������� ������ ������� ������������� �����
{
    glm::vec3 Position;                                                                 //������ ������� ��� ������ �������
    glm::vec3 Normal;                                                                   //����� ������� ��� ������ �������
    glm::vec2 TexCoords;                                                                //���������� ���������� ������ �������
};

struct Texture                                                                          //������ ���������� ������ ��� ������ �������
{
    GLuint id;                            
    string type;                                                                        //��� ��������(��������� ��� ��������)
    aiString path;                                                                      //���� � ��������
};

class Mesh                                                                              //������������� �����
{
public:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

    void Draw(Shader& shader);                                                          //���������. ������������� �����
private:
    GLuint VAO, VBO, EBO;

    void setupMesh();                                                                   //�������������� ������
};