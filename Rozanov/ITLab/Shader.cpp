#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath,  const GLchar* geometryPath)     //const GLchar* - текст - путь к файлу с кодом шейдера
{
                           
    string vertexCode;                                                                                //переменные для получение исходного кода вершинного шейдера
    string fragmentCode;                                                                              //переменные для получение исходного кода фрагментного шейдера
    string geometryCode;                                                                              //переменные для получение исходного кода геометрического шейдера
    ifstream vShaderFile;                                                                             //переменные для получение исходного кода вершинного шейдера
    ifstream fShaderFile;                                                                             //переменные для получение исходного кода фрагментного шейдера
    ifstream gShaderFile;                                                                             //переменные для получение исходного кода геометрического шейдера

    
    vShaderFile.exceptions(ifstream::failbit);                                                        //проверка на выброс исключения Объектов ifstream
    fShaderFile.exceptions(ifstream::failbit);                                                        //проверка на выброс исключения Объектов ifstream
    gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);                                     //проверка на выброс исключения Объектов ifstream
    try
    {
        vShaderFile.open(vertexPath);                                                                 // Открываем файлы векторного шейдера
        fShaderFile.open(fragmentPath);                                                               // Открываем файлы фрагментного шейдера
        stringstream vShaderStream;                                                                   //поток для векторного шейдера
        stringstream   fShaderStream;                                                                 //поток для фрагментного шейдера
        vShaderStream << vShaderFile.rdbuf();                                                         //Считываем данные векторного шейдера в поток для векторного шейдера
        fShaderStream << fShaderFile.rdbuf();                                                         //Считываем данные фрагментного шейдера в поток для фрагментного шейдера
        vShaderFile.close();                                                                          //Закрываем файл с векторным шейдером                                                       
        fShaderFile.close();                                                                          //Закрываем файлы  с вершинным шейдером   
    
        vertexCode = vShaderStream.str();                                                             //Преобразовываем поток векторного шейдера в массив GLchar
        fragmentCode = fShaderStream.str();                                                           //Преобразовываем поток фрагментного шейдера в массив GLchar
    
        if (geometryPath != nullptr)                                                                  //если передан путь к геометрическому шейдеру (если const GLchar* не null)                 
        {
            gShaderFile.open(geometryPath);                                                           //открываем геометрический шейдер
            stringstream gShaderStream;                                                               //создаем поток для геометрического шейдера
            gShaderStream << gShaderFile.rdbuf();                                                     //считываем в поток для геометрического шейдера
            gShaderFile.close();                                                                      //закрываем файл с геомтерическим шейедром
            geometryCode = gShaderStream.str();                                                       //преобразовываем поток геомтерического шейдера в текст
        }
    }
    catch (std::ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

    const GLchar* vShaderCode = vertexCode.c_str();                                                 //получаем строку кода для векторного шейдера, в конце которой записан null
    const GLchar* fShaderCode = fragmentCode.c_str();                                               //получаем строку кода для фрагментного шейдера, в конце которой записан null

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    GLuint geometry;
    if (geometryPath != nullptr)
    {
        const char* gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        if (!success)
        {
            glGetShaderInfoLog(geometry, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    //Шейдерная программа
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    if (geometryPath != nullptr)
    {
        glAttachShader(Program, geometry);
    }
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath != nullptr)
    {
        glDeleteShader(geometry);
    }
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(Program, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(Program, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(Program, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(Program, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(Program, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(Program, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(Program, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(Program, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(Program, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::Use()
{
    glUseProgram(this->Program);
}
