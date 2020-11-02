#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)                //��������� �� ������ ��������(����� - ���� � ����� � ����� �������)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //�������� �� ������ ���������� �������� ifstream
    vShaderFile.exceptions(std::ifstream::failbit);
    fShaderFile.exceptions(std::ifstream::failbit);
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
    // Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // Print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // Print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // Shader Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    // Print linking errors if any
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(this->Program);
}
