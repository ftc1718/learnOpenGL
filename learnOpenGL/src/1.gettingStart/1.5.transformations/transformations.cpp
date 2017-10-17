#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#include "../../utility/shader.h"


void frameBufferSize_callBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "hello world", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSize_callBack);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad!" << std::endl;
		return -1;
	}

	//GLint nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

	//std::cout << nrAttributes << std::endl;

	Shader ourShader("src/1.gettingStart/1.5.transformations/transformation.vs", "src/1.gettingStart/1.5.transformations/transformation.fs");

	float vertices[] = {
		//position          //texture
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};


	unsigned int vertexBufferObj;
	unsigned int indexBufferObj;
	unsigned int vertexArrayObj;
	glGenVertexArrays(1, &vertexArrayObj);
	glGenBuffers(1, &vertexBufferObj);
	glGenBuffers(1, &indexBufferObj);

	glBindVertexArray(vertexArrayObj);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObj);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//generate texture
	unsigned int texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channel;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("../res/textures/container.jpg", &width, &height, &channel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture0" << std::endl;
	}
	stbi_image_free(data);

	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("../res/textures/awesomeface.png", &width, &height, &channel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture1" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use();
	ourShader.setInt("texture0", 0);
	ourShader.setInt("texture1", 1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glm::mat4 transform;
		/*transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 0.5f));*/

		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		unsigned int transformLoc = glGetUniformLocation(ourShader.m_prorgamID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(vertexArrayObj);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		transform = glm::mat4();
		transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
		transform = glm::scale(transform, glm::vec3(sin(glfwGetTime()) + 1.0f) / 2.0f);
		//float scaleAmount = sin(glfwGetTime());
		//transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));

		transformLoc = glGetUniformLocation(ourShader.m_prorgamID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(vertexArrayObj);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vertexArrayObj);
	glDeleteBuffers(1, &indexBufferObj);
	glDeleteBuffers(1, &vertexBufferObj);

	glfwTerminate();
	return 0;
}
