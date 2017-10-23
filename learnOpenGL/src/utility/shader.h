#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	void setVec3(const GLchar* name, const glm::vec3& value) const;
	void setVec3(const GLchar* name, float x, float y, float z) const;

	void setMat4(const GLchar* name, const glm::mat4& value) const;
};