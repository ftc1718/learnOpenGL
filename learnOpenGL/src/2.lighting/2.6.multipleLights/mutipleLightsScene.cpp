#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

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

	//GLint nrAttributes;
	//glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);

	//std::cout << nrAttributes << std::endl;

	Shader objectShader("src/2.lighting/2.6.multipleLights/multipleLights.vs", "src/2.lighting/2.6.multipleLights/multipleLights.fs");
	Shader lightShader("src/2.lighting/2.6.multipleLights/lamp.vs", "src/2.lighting/2.6.multipleLights/lamp.fs");

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	unsigned int vertexBufferObj;
	unsigned int vertexArrayObj;
	glGenVertexArrays(1, &vertexArrayObj);
	glGenBuffers(1, &vertexBufferObj);

	glBindVertexArray(vertexArrayObj);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int diffuseMap = loadTexture("../res/textures/container2.png");
	unsigned int specularMap = loadTexture("../res/textures/container2_specular.png");

	objectShader.use();
	objectShader.setInt("material.diffuse", 0);
	objectShader.setInt("material.specular", 1);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		objectShader.use();
		objectShader.setVec3("viewPos", camera.getPosition());
		objectShader.setFloat("material.shininess", 32.0f);

		// == ==============================================================================================
		//       DESERT
		// == ==============================================================================================

		glClearColor(0.75f, 0.5f, 0.3f, 1.0f);

		glm::vec3 pointLightColors[] = {
			glm::vec3(1.0f, 0.6f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 1.0, 0.0),
			glm::vec3(0.2f, 0.2f, 1.0f)
		};

		// directional light
		objectShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		objectShader.setVec3("dirLight.ambient", 0.3f, 0.2f, 0.1f);
		objectShader.setVec3("dirLight.diffuse", 0.7f, 0.4f, 0.3f);
		objectShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		objectShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		objectShader.setVec3("pointLights[0].ambient", pointLightColors[0] * 0.1f);
		objectShader.setVec3("pointLights[0].diffuse", pointLightColors[0]);
		objectShader.setVec3("pointLights[0].specular", pointLightColors[0]);
		objectShader.setFloat("pointLights[0].constant", 1.0f);
		objectShader.setFloat("pointLights[0].linear", 0.09);
		objectShader.setFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		objectShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		objectShader.setVec3("pointLights[1].ambient", pointLightColors[1] * 0.1f);
		objectShader.setVec3("pointLights[1].diffuse", pointLightColors[1]);
		objectShader.setVec3("pointLights[1].specular", pointLightColors[1]);
		objectShader.setFloat("pointLights[1].constant", 1.0f);
		objectShader.setFloat("pointLights[1].linear", 0.09);
		objectShader.setFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		objectShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		objectShader.setVec3("pointLights[2].ambient", pointLightColors[2] * 0.1f);
		objectShader.setVec3("pointLights[2].diffuse", pointLightColors[2]);
		objectShader.setVec3("pointLights[2].specular", pointLightColors[2]);
		objectShader.setFloat("pointLights[2].constant", 1.0f);
		objectShader.setFloat("pointLights[2].linear", 0.09);
		objectShader.setFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		objectShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		objectShader.setVec3("pointLights[3].ambient", pointLightColors[3] * 0.1f);
		objectShader.setVec3("pointLights[3].diffuse", pointLightColors[3]);
		objectShader.setVec3("pointLights[3].specular", pointLightColors[3]);
		objectShader.setFloat("pointLights[3].constant", 1.0f);
		objectShader.setFloat("pointLights[3].linear", 0.09);
		objectShader.setFloat("pointLights[3].quadratic", 0.032);
		// spotLight
		objectShader.setVec3("spotLight.position", camera.getPosition());
		objectShader.setVec3("spotLight.direction", camera.getFront());
		objectShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		objectShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		objectShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		objectShader.setFloat("spotLight.constant", 1.0f);
		objectShader.setFloat("spotLight.linear", 0.09);
		objectShader.setFloat("spotLight.quadratic", 0.032);
		objectShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		objectShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		glm::mat4 projection, view;
		projection = glm::perspective(glm::radians(camera.getZoom()), 800.0f / 600.0f, 0.1f, 100.0f);
		view = camera.getViewMatrix();
		objectShader.setMat4("projection", projection);
		objectShader.setMat4("view", view);

		glm::mat4 model;
		objectShader.setMat4("model", model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		glBindVertexArray(vertexArrayObj);
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			objectShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightShader.use();
		lightShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);

		glBindVertexArray(lightVAO);
		for (int i = 0; i < 4; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lightShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vertexArrayObj);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &vertexBufferObj);

	glfwTerminate();
	return 0;
}
