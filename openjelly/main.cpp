#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"
#include "shader.h"
#include "camera.h"
#include "vertexarray.h"

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
		// Positions           // Normals           // Texture Coords
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

	Shader boxShader  ("shaders/basic.vert", "shaders/basic.frag");
	Shader lightShader("shaders/light.vert", "shaders/light.frag");

	std::string filename = "images/container2.png";
	int tW, tH, tC;
	unsigned char* texImage = stbi_load(filename.c_str(), &tW, &tH, &tC, STBI_rgb);

	GLuint diffuseMap;
	glGenTextures(1, &diffuseMap);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tW, tH, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(texImage);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	VertexArray container(VBO, &boxShader);
	container.enableAttrib(0, 3, 0);
	container.enableAttrib(1, 3, 3);
	container.enableAttrib(2, 2, 6);

	VertexArray light(VBO, &lightShader);
	light.enableAttrib(0, 3, 0);

	Camera camera(glm::vec3(-1.0f, 1.0f, 4.0f));

	while (!window.closed()) {

		window.clear(0.1f, 0.1, 0.1f);

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();

		processMovement(&camera, &window);

		lightPos.x = 1.0f + std::sin(glfwGetTime()) * 2.0f;
		lightPos.y = std::sin(glfwGetTime() / 2.0f) * 1.0f;

		boxShader.setUniform("viewPos", camera.position);

		boxShader.setUniform("light.position", lightPos);
		boxShader.setUniform("light.ambient",  1.0f, 1.0f, 1.0f);
		boxShader.setUniform("light.diffuse",  1.0f, 1.0f, 1.0f);
		boxShader.setUniform("light.specular", 1.0f, 1.0f, 1.0f);

		boxShader.setUniform("material.ambient", 0.05375f, 0.05f, 0.06625f);
		boxShader.setUniform("material.diffuse", 0.0f);
		boxShader.setUniform("material.specular", 0.332741f, 0.328634f, 0.346435f);
		boxShader.setUniform("material.shininess", 38.0f);

		glm::mat4 model, view, projection;
		view = camera.getView();
		projection = glm::perspective(camera.fov, (GLfloat)(window.getWidth() / window.getHeight()), 0.1f, 100.0f);

		boxShader.setUniform("model", &model);
		boxShader.setUniform("view", &view);
		boxShader.setUniform("projection", &projection);

		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.1f));

		lightShader.setUniform("model", &model);
		lightShader.setUniform("view", &view);
		lightShader.setUniform("projection", &projection);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		container.draw(36);
		light.draw(36);
		
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
