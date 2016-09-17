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

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void processMovement(Camera* camera, Window* window);

int main() {

	Window window("OpenJelly", 600, 600);

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
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

	Camera camera(glm::vec3(-1.0f, 1.0f, 3.0f));

	Shader boxShader  ("shaders/basic.vert", "shaders/basic.frag");
	Shader lightShader("shaders/light.vert", "shaders/light.frag");

	Texture diffuseMap("images/container2.png");
	Texture specularMap("images/container2_specular.png");

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

	boxShader.setUniform("light.ambient",  0.1f, 0.1f, 0.1f);
	boxShader.setUniform("light.diffuse",  0.8f, 0.8f, 0.8f);
	boxShader.setUniform("light.specular", 1.0f, 1.0f, 1.0f);
	boxShader.setUniform("light.constant", 1.0f);
	boxShader.setUniform("light.linear", 0.09f);
	boxShader.setUniform("light.quadratic", 0.032f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap.id);
	boxShader.setUniform("material.diffuse", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap.id);
	boxShader.setUniform("material.specular", 1);

	boxShader.setUniform("material.shininess", 32.0f);

	while (!window.closed()) {

		window.clear(0.1f, 0.1, 0.1f);

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();

		processMovement(&camera, &window);

		boxShader.setUniform("viewPos", camera.position);

		boxShader.setUniform("dirLight.direction", -0.2f, -1.0f, -0.3f);
		boxShader.setUniform("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		boxShader.setUniform("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		boxShader.setUniform("dirLight.specular", 0.5f, 0.5f, 0.5f);
		
		boxShader.setUniform("pointLights[0].position", pointLightPositions[0]);
		boxShader.setUniform("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		boxShader.setUniform("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		boxShader.setUniform("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		boxShader.setUniform("pointLights[0].constant", 1.0f);
		boxShader.setUniform("pointLights[0].linear", 0.09f);
		boxShader.setUniform("pointLights[0].quadratic", 0.032f);

		boxShader.setUniform("pointLights[1].position", pointLightPositions[1]);
		boxShader.setUniform("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		boxShader.setUniform("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		boxShader.setUniform("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		boxShader.setUniform("pointLights[1].constant", 1.0f);
		boxShader.setUniform("pointLights[1].linear", 0.09f);
		boxShader.setUniform("pointLights[1].quadratic", 0.032f);

		boxShader.setUniform("pointLights[2].position", pointLightPositions[2]);
		boxShader.setUniform("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		boxShader.setUniform("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		boxShader.setUniform("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		boxShader.setUniform("pointLights[2].constant", 1.0f);
		boxShader.setUniform("pointLights[2].linear", 0.09f);
		boxShader.setUniform("pointLights[2].quadratic", 0.032f);

		boxShader.setUniform("pointLights[3].position", pointLightPositions[3]);
		boxShader.setUniform("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		boxShader.setUniform("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		boxShader.setUniform("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		boxShader.setUniform("pointLights[3].constant", 1.0f);
		boxShader.setUniform("pointLights[3].linear", 0.09f);
		boxShader.setUniform("pointLights[3].quadratic", 0.032f);

		glm::mat4 model, view, projection;
		view = camera.getView();
		projection = glm::perspective(camera.fov, (GLfloat)(window.getWidth() / window.getHeight()), 0.1f, 100.0f);

		boxShader.setUniform("view", &view);
		boxShader.setUniform("projection", &projection);

		for (GLuint i = 0; i < 10; i++)
		{
			model = glm::mat4();
			model = glm::translate(model, cubePositions[i]);
			GLfloat angle = 20.0f * i;
			model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
			boxShader.setUniform("model", &model);
			container.draw(36);
		}

		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4();
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
			lightShader.setUniform("model", &model);
			lightShader.setUniform("view", &view);
			lightShader.setUniform("projection", &projection);
			light.draw(36);
		}

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
