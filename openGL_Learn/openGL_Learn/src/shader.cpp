#include "shader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ��֤ifstream��������׳��쳣��
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // ���ļ�
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // ��ȡ�ļ��Ļ������ݵ���������
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // �ر��ļ�������
        vShaderFile.close();
        fShaderFile.close();
        // ת����������string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();



	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	int ret;
	char log[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &ret);
	if (!ret)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, log);
		std::cout << "vertexShader Error:" << log << std::endl;

		return;
	}

	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fShaderCode, NULL);
	glCompileShader(fragShader);

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &ret);
	if (!ret)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, log);
		std::cout << "fragmentShader Error:" << log << std::endl;
		return;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &ret);
	if (!ret)
	{
		glGetProgramInfoLog(ID, 512, NULL, log);
		std::cout << "shaderProgram Error:" << log << std::endl;

		return;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void Shader::use() 
{
	glUseProgram(ID);
}

void Shader::setFloat(const std::string& name, float value) const 
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform1f(location, value);
}
void Shader::setInt(const std::string& name, int value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, value);
}
void Shader::setBool(const std::string& name, bool value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform1i(location, (int)value);
}

void Shader::setFloat4(const std::string& name, float value0, float value1, float value2, float value3) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	glUniform4f(location, value0, value1, value2, value3);
}

void Shader::setFloat4x4(const std::string& name, const float* value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());

	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void Shader::setFloat4x4(const std::string& name,int count, bool transpose, const glm::mat4 value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());

	float temp[16];
	for (int i = 0; i < 4; i++)
	{
		temp[i] = value[i].x;
		temp[i+1] = value[i].y;
		temp[i+2] = value[i].z;
		temp[i+3] = value[i].w;
	}

	glUniformMatrix4fv(location, count, transpose, temp);
}