#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->vertices = vertices;                                                                      //�������
    this->indices = indices;                                                                        //�������
    this->textures = textures;                                                                      //��������

    setupMesh();
}

void Mesh::Draw(Shader& shader)
{
    GLuint diffuseNr = 1;                                                                           //��������� ��������
    GLuint specularNr = 1;                                                                          //�������� ��������
    GLuint normalNr = 1;
    GLuint heightNr = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);                                                           //���������� ��������
        
        string number;
        string name = textures[i].type;                                                             //������ ��� �������� (�� ��������� ��������)
        if (name == "texture_diffuse")
        {    
            number = to_string(diffuseNr++);                                                   // ������ ����������� diffuse ��������, ...
        }
        else 
        {
            if (name == "texture_specular")
            {
                number = to_string(specularNr++); 
            }
            else
            {
                if (name == "texture_normal")
                {
                    number = to_string(normalNr++); 
                }
                else
                {
                    if (name == "texture_height")
                    {
                        number = to_string(heightNr++);
                    }
                }
            }
        }
        glUniform1i(glGetUniformLocation(shader.Program, (name + number).c_str()), i);                    //���������� �������� �� ��������
        glBindTexture(GL_TEXTURE_2D, textures[i].id);                                                     //������ ��������, 
    }

    //----// �������������� mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);       
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);                                                                         //����������� �������� ���������� � �� ��������������� ��������
}

void Mesh::setupMesh()
{
    glGenBuffers(1, &VBO);															                        //������� VBO ����� ��� �������,											
    glGenVertexArrays(1, &VAO);														                        //VAO
    glGenBuffers(1, &EBO);															                        //EBO
    //----//
    glBindVertexArray(VAO);                                                                                 //������ VAO(-> ���������� �������� VBO � ��������� �� �������� � VAO)
    //----//
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                                     //��� ������, ������� ����� ������� VBO ����� � ������ GL_ARRAY_BUFFER(������ ����� GL_ARRAY_BUFFER. ������ ����� �����, ������������ �����, ����� �������� � VBO.)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //----//
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);              //�������� ���� ������� � ����� ��� OpenGL.1�������� �  ��� ������ � ������� �� ����� ����������� ������ (��� VBO ������ �������� � GL_ARRAY_BUFFER). 2�� - ���������� ���������� ������ (� ������), ������� ����� �������� ������. 3 �������� � ���  ������. 4�������� ���������� ��� �� ����� ����� ���������� �������� � ����������� �� �������(3 ������:GL_STATIC_DRAW: ������ ���� ������� �� ����� ����������(������ � ������� ������������ �������� �� �����), ���� ����� ���������� ����� �����; GL_DYNAMIC_DRAW: ������ ����� �������� �������� �����;GL_STREAM_DRAW: ������ ����� �������� ��� ������ ���������) (������ ��� ����������)).
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);  //�������� ������� ������ � EBO
    //----//
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);                              //������� ��� ������ : ������������� ��������� �� ��������� ��������. 1 - �� �������� - ����� �������� ������� ����� ���������(position - layout(location = 0)), 2�� �������� - ������ ���������(�.�.vec3), 3��  ������������ ��� ������, 4�� ��������� ������������� ������������� ������� ������(���� ������ GL_TRUE, �� ��� ������ ����� ����������� ����� 0 (-1 ��� �������� ��������) � 1. ������������ �� ���������->��������� GL_FALSE), 5�� ���(��������� ���������� ����� �������� ������), 6�� - ����� ��� GLvoid * ->���������� ���������� �����. - ��� �������� ������ ������ � ������(� ��� ����� �� ����� �������� � �������  ��������� 0)
    glEnableVertexAttribArray(0);                                                                           //��� �������
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));       //OFFSETOF ���������� �������� � ������ ��������� ���������� �� ���������� �� ������ ���������  
    glEnableVertexAttribArray(1);                                                                           //��� �������
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));    //5)������� ������������ ��������
    glEnableVertexAttribArray(2);                                                                           //��� �������
   
    glBindVertexArray(0);                                                                                   //����� VAO. (����� ����� ����� ��������� "glBindVertexArray(VAO);" � ����� ����� ��������)
}
