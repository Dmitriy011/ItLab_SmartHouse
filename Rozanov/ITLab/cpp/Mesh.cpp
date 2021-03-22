#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
    this->vertices = vertices;                                                                      //Вершины
    this->indices = indices;                                                                        //Индексы
    this->textures = textures;                                                                      //Текстуры

    setupMesh();
}

void Mesh::Draw(Shader& shader)
{
    GLuint diffuseNr = 1;                                                                           //диффузная текстура
    GLuint specularNr = 1;                                                                          //бликовая текстура
    GLuint normalNr = 1;
    GLuint heightNr = 1;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);                                                           //активируем текстуры
        
        string number;
        string name = textures[i].type;                                                             //Узнаем тип текстуры (Из структуры текстуры)
        if (name == "texture_diffuse")
        {    
            number = to_string(diffuseNr++);                                                   // Узнаем колличество diffuse текстуры, ...
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
        glUniform1i(glGetUniformLocation(shader.Program, (name + number).c_str()), i);                    //Генерируем картинку на текстуру
        glBindTexture(GL_TEXTURE_2D, textures[i].id);                                                     //привяз текстуру, 
    }

    //----// Отрисовывается mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);       
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);                                                                         //возвращение значению переменной к ее первоначальному значению
}

void Mesh::setupMesh()
{
    glGenBuffers(1, &VBO);															                        //Создаем VBO через эту функцию,											
    glGenVertexArrays(1, &VAO);														                        //VAO
    glGenBuffers(1, &EBO);															                        //EBO
    //----//
    glBindVertexArray(VAO);                                                                                 //Привяз VAO(-> необходимо привзять VBO и указатели на атрибуты к VAO)
    //----//
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                                     //Все данные, которые хотим хранить VBO будут в буфере GL_ARRAY_BUFFER(привяз буфер GL_ARRAY_BUFFER. Теперь любой вызов, использующий буфер, будет работать с VBO.)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //----//
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);              //Копируем наши вершины в буфер для OpenGL.1аргумент —  тип буфера в который мы хотим скопировать данные (наш VBO сейчас привязан к GL_ARRAY_BUFFER). 2ой - определяет количество данных (в байтах), которые хотим передать буферу. 3 аргумент — это  данные. 4аргумент определяет как мы хотим чтобы видеокарта работала с переданными ей данными(3 режима:GL_STATIC_DRAW: данные либо никогда не будут изменяться(Данные о позиции треугольника меняться не будут), либо будут изменяться очень редко; GL_DYNAMIC_DRAW: данные будут меняться довольно часто;GL_STREAM_DRAW: данные будут меняться при каждой отрисовке) (Данные для видеокарты)).
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_DYNAMIC_DRAW);  //Копируем индексы врешин в EBO
    //----//
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);                              //Атрибут для вершин : Устанавливаем указатели на вершинные атрибуты. 1 - ый аргумент - какой параметр шейдера хотим настриоть(position - layout(location = 0)), 2ой аргумент - размер аргумента(т.к.vec3), 3ий  используемый тип данных, 4ый указывает необходимость нормализовать входные данные(Если укажем GL_TRUE, то все данные будут расположены между 0 (-1 для знаковых значений) и 1. Нормализация не требуется->оставляем GL_FALSE), 5ый шаг(описывает расстояние между наборами данных), 6ой - имеет тип GLvoid * ->необходимо приведение типов. - ЭТО смещение начала данных в буфере(У нас буфер не имеет смещения и поэтому  указываем 0)
    glEnableVertexAttribArray(0);                                                                           //Вкл атрибут
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));       //OFFSETOF ВОЗВРАЩАЕТ СМЕЩЕНИЕ В БАЙТАХ УКАЗАННОЙ ПЕРЕМЕННОЙ ДО ПЕРЕМЕННОЙ ВО ВТОРОМ АРГУМЕНТЕ  
    glEnableVertexAttribArray(1);                                                                           //Вкл атрибут
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));    //5)Атрибут расположения текстуры
    glEnableVertexAttribArray(2);                                                                           //Вкл атрибут
   
    glBindVertexArray(0);                                                                                   //Отвзя VAO. (Далее можно снова привязать "glBindVertexArray(VAO);" и необх снова отвязать)
}
