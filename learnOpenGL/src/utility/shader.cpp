#include "shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);

	std::stringstream vShaderStream;
	std::stringstream fShaderStream;
	vShaderStream << vShaderFile.rdbuf();
	fShaderStream << fShaderFile.rdbuf();

	vShaderFile.close();
	fShaderFile.close();

	std::string vertexCode;
	std::string fragmentCode;
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	unsigned int vertexShader, fragmentShader;
	int success;
	char infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::FRAGMENT::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	m_prorgamID = glCreateProgram();
	glAttachShader(m_prorgamID, vertexShader);
	glAttachShader(m_prorgamID, fragmentShader);
	glLinkProgram(m_prorgamID);

	glGetProgramiv(m_prorgamID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_prorgamID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(m_prorgamID);
}

void Shader::setBool(const GLchar* name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_prorgamID, name), (int)value);
}

void Shader::setInt(const GLchar* name, int value) const
{
	glUniform1i(glGetUniformLocation(m_prorgamID, name), value);
}

void Shader::setFloat(const GLchar* name, float value) const
{
	glUniform1f(glGetUniformLocation(m_prorgamID, name), value);
}

void Shader::setVec3(const GLchar* name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(m_prorgamID, name), 1, &value[0]);
}

void Shader::setVec3(const GLchar* name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_prorgamID, name), x, y, z);
}

void Shader::setMat4(const GLchar* name, const glm::mat4& value) const 
{
	glUniformMatrix4fv(glGetUniformLocation(m_prorgamID, name), 1, GL_FALSE, glm::value_ptr(value));
}