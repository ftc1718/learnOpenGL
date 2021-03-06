#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>

#include "../../utility/shader.h"
#include "../../utility/camera.h"
#include "../../utility/utility.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = 400.0f;
float lastY = 300.0f;

bool firstMouse = true;

//camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void frameBufferSize_callBack(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callBack(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	//	float yOffset = ypos - lastY; // mouse reverse
	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xOffset, yOffset);
}

void mouseScroll_callBack(GLFWwindow* window, double xOffset, double yOffset)
{
	camera.processMouseScroll(yOffset);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.processKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.processKeyboard(BACKWARD, deltaTime);
	}
	//cross(cameraFront, cameraUp) to create a right vector
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.processKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.processKeyboard(RIGHT, deltaTime);
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
	glfwSetCursorPosCallback(window, mouse_callBack);
	glfwSetScrollCallback(window, mouseScroll_callBack);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize glad!" << std::endl;
		return -1;
	}

	Shader shader("src/4.advancedOpneGL/4.4.faceCulling/faceCulling.vs", "src/4.advancedOpneGL/4.4.faceCulling/faceCulling.fs");

	//in order to face culling the vertex order must be counter-clockwise order
	float cubeVertices[] = {
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		  0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		 // Front face
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		  0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		  0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
		 -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
		 // Left face
		 -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		 -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		 -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
		 // Right face
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
		 // Bottom face
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		  0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
		 // Top face
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left  
	};

	//cube
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);

	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);


	unsigned int cubeTexture = loadTexture("../res/textures/marble.jpg");

	shader.use();
	shader.setInt("texture1", 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
//	glCullFace(GL_FRONT);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection, view;
		projection = glm::perspective(glm::radians(camera.getZoom()), 800.0f / 600.0f, 0.1f, 100.0f);
		view = camera.getViewMatrix();

		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		// draw cubes
		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubeTexture);
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);


	glfwTerminate();
	return 0;
}
