#include <iostream>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"
#include "shader.h"
#include "camera.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLfloat lastX = 400;
GLfloat lastY = 300;
bool firstMouseMove = true;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void processMovement(Camera* camera, Window* window);

int main() {

	Window window("OpenJelly", 800, 600);

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	Shader boxShader  ("shaders/basic.vs", "shaders/basic.frag");
	Shader lightShader("shaders/light.vs", "shaders/light.frag");

	GLuint VBO, containerVAO, lightVAO;
	glGenVertexArrays(1, &containerVAO);
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(containerVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));


	while (!window.closed()) {

		window.clear();

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();

		processMovement(&camera, &window);

		boxShader.use();
		GLint objectColourLoc = glGetUniformLocation(boxShader.program, "objectColour");
		GLint lightColourLoc  = glGetUniformLocation(boxShader.program, "lightColour");
		glUniform3f(objectColourLoc, 1.0f, 0.5f, 0.31f);
		glUniform3f(lightColourLoc,  1.0f, 0.5f, 1.0f);

		glm::mat4 model, view, projection;
		view = camera.getView();
		projection = glm::perspective(camera.fov, (GLfloat)(window.getWidth() / window.getHeight()), 0.1f, 100.0f);

		GLint modelLoc		= glGetUniformLocation(boxShader.program, "model");
		GLint viewLoc		= glGetUniformLocation(boxShader.program, "view");
		GLint projectionLoc = glGetUniformLocation(boxShader.program, "projection");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(containerVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		lightShader.use();
		modelLoc = glGetUniformLocation(lightShader.program, "model");
		viewLoc = glGetUniformLocation(lightShader.program, "view");
		projectionLoc = glGetUniformLocation(lightShader.program, "projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		window.update();

	}

	return 0;

}


void processMovement(Camera* camera, Window* window) {

	if (window->isKeyPressed(GLFW_KEY_W))
		camera->move(FORWARD, window->delta);

	if (window->isKeyPressed(GLFW_KEY_S))
		camera->move(BACKWARDS, window->delta);

	if (window->isKeyPressed(GLFW_KEY_A))
		camera->move(LEFT, window->delta);

	if (window->isKeyPressed(GLFW_KEY_D))
		camera->move(RIGHT, window->delta);

	if (window->isKeyPressed(GLFW_KEY_SPACE))
		camera->move(UP, window->delta);

	if (window->isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		camera->move(DOWN, window->delta);

	if (window->hasMouseMoved()) {

		if (firstMouseMove) {
			lastX = window->getMousePosition().x;
			lastY = window->getMousePosition().y;
			firstMouseMove = false;
		}

		glm::vec2 mousePos = window->getMousePosition();

		GLfloat xoffset = mousePos.x - lastX;	
		GLfloat yoffset = mousePos.y - lastY;

		lastX = mousePos.x;
		lastY = mousePos.y;

		camera->look(xoffset, yoffset);
	}
}
