#pragma once
#include <glad/glad.h>

class Shader
{
private:
	GLuint m_prorgamID;
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void use();

	void setBool(const GLchar* name, bool value) const;
	void setInt(const GLchar* name, int value) const;
	void setFloat(const GLchar* name, float value) const;
};