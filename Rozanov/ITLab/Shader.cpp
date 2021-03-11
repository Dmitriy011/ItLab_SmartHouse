#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath,  const GLchar* geometryPath)     //const GLchar* - ����� - ���� � ����� � ����� �������
{
                           
    string vertexCode;                                                                                //���������� ��� ��������� ��������� ���� ���������� �������
    string fragmentCode;                                                                              //���������� ��� ��������� ��������� ���� ������������ �������
    string geometryCode;                                                                              //���������� ��� ��������� ��������� ���� ��������������� �������
    ifstream vShaderFile;                                                                             //���������� ��� ��������� ��������� ���� ���������� �������
    ifstream fShaderFile;                                                                             //���������� ��� ��������� ��������� ���� ������������ �������
    ifstream gShaderFile;                                                                             //���������� ��� ��������� ��������� ���� ��������������� �������

    
    vShaderFile.exceptions(ifstream::failbit);                                                        //�������� �� ������ ���������� �������� ifstream
    fShaderFile.exceptions(ifstream::failbit);                                                        //�������� �� ������ ���������� �������� ifstream
    gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);                                     //�������� �� ������ ���������� �������� ifstream
    try
    {
        vShaderFile.open(vertexPath);                                                                 // ��������� ����� ���������� �������
        fShaderFile.open(fragmentPath);                                                               // ��������� ����� ������������ �������
        stringstream vShaderStream;                                                                   //����� ��� ���������� �������
        stringstream   fShaderStream;                                                                 //����� ��� ������������ �������
        vShaderStream << vShaderFile.rdbuf();                                                         //��������� ������ ���������� ������� � ����� ��� ���������� �������
        fShaderStream << fShaderFile.rdbuf();                                                         //��������� ������ ������������ ������� � ����� ��� ������������ �������
        vShaderFile.close();                                                                          //��������� ���� � ��������� ��������                                                       
        fShaderFile.close();                                                                          //��������� �����  � ��������� ��������   
    
        vertexCode = vShaderStream.str();                                                             //��������������� ����� ���������� ������� � ������ GLchar
        fragmentCode = fShaderStream.str();                                                           //��������������� ����� ������������ ������� � ������ GLchar
    
        if (geometryPath != nullptr)                                                                  //���� ������� ���� � ��������������� ������� (���� const GLchar* �� null)                 
        {
            gShaderFile.open(geometryPath);                                                           //��������� �������������� ������
            stringstream gShaderStream;                                                               //������� ����� ��� ��������������� �������
            gShaderStream << gShaderFile.rdbuf();                                                     //��������� � ����� ��� ��������������� �������
            gShaderFile.close();                                                                      //��������� ���� � �������������� ��������
            geometryCode = gShaderStream.str();                                                       //��������������� ����� ��������������� ������� � �����
        }
    }
    catch (std::ifstream::failure e)
    {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }

    const GLchar* vShaderCode = vertexCode.c_str();                                                 //�������� ������ ���� ��� ���������� �������, � ����� ������� ������� null
    const GLchar* fShaderCode = fragmentCode.c_str();                                               //�������� ������ ���� ��� ������������ �������, � ����� ������� ������� null

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

    //��������� ���������
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
