#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath,  const GLchar* geometryPath)                //��������� �� ������ ��������(����� - ���� � ����� � ����� �������)
{
    //----//  ��������� ��������� ���� ����������/������������/��������������� �������
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;

    //�������� �� ������ ���������� �������� ifstream
    vShaderFile.exceptions(std::ifstream::failbit);
    fShaderFile.exceptions(std::ifstream::failbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);                                                      //1) ��������� �����
        fShaderFile.open(fragmentPath);                                                    //1) ��������� �����
        std::stringstream vShaderStream, fShaderStream; 
        vShaderStream << vShaderFile.rdbuf();                                              //2)��������� ������ � ������
        fShaderStream << fShaderFile.rdbuf();                                              //2)��������� ������ � ������
        
        vShaderFile.close();                                                               //3)��������� �����                                                        
        fShaderFile.close();                                                               //3)��������� �����    
    
        vertexCode = vShaderStream.str();                                                  //4)��������������� ������ � ������ GLchar
        fragmentCode = fShaderStream.str();                                                //4)��������������� ������ � ������ GLchar
    
        if (geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

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
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if (geometryPath != nullptr)
    {
        glDeleteShader(geometry);
    }
}

void Shader::Use()
{
    glUseProgram(this->Program);
}
