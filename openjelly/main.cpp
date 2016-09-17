#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"
#include "shader.h"
#include "camera.h"
#include "texture.h"
#include "vertexarray.h"

GLfloat lastX = 400;
GLfloat lastY = 300;
bool firstMouseMove = true;

void processMovement(Camera* camera, Window* window);

int main() {

	Window window("OpenJelly", 600, 600);

	Camera camera(glm::vec3(-1.0f, 1.0f, 3.0f));

	Shader boxShader  ("shaders/basic.vert", "shaders/basic.frag");

	while (!window.closed()) {

		window.clear(0.1f, 0.1, 0.1f);

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();

		processMovement(&camera, &window);

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
