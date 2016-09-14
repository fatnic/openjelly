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

void processMovement(Camera* camera, Window* window);

int main() {

	Window window("OpenJelly", 800, 600);

	std::vector<GLfloat> vertices = {
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,	  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,	  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,	 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,	 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,	  0.0f, 1.0f
	};
	std::vector<glm::vec3> boxes = {
		glm::vec3(1.05f, 1.05f, 0.0f),
		glm::vec3(1.005f,  0.0f,  0.0f),
		glm::vec3(1.005f, -1.005f, 0.0f),

		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(0.0f,  1.005f, 0.0f),
		glm::vec3(0.0f, -1.005f, 0.0f),

		glm::vec3(-1.05f, 1.05f, 0.0f),
		glm::vec3(-1.005f,  0.0f,  0.0f),
		glm::vec3(-1.005f, -1.005f, 0.0f),
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

	std::string filename = "images/container2.png";
	int tW, tH, tC;
	unsigned char* texImage = stbi_load(filename.c_str(), &tW, &tH, &tC, STBI_rgb);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tW, tH, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(texImage);

	Shader shader("shaders/basic.vs", "shaders/basic.frag");
	shader.use();

	glClearColor(0.2f, 0.3f, 0.7f, 1.0f);

	Camera camera(glm::vec3(0.0f, 0.0f, 6.0f));

	glm::mat4 view, projection, transform;
	projection = glm::perspective(camera.fov, (GLfloat)(window.getWidth() / window.getHeight()), 0.1f, 100.0f);

	GLint transformLoc = glGetUniformLocation(shader.program, "transform");
	
	while (!window.closed()) {

		if (window.isKeyPressed(GLFW_KEY_ESCAPE))
			window.close();
		
		processMovement(&camera, &window);

		window.clear();
		
		view = camera.getView();

		for (glm::vec3 box : boxes) {
			glm::mat4 model;
			model = glm::translate(model, box);
			transform = projection * view * model;
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
			glDrawArrays(GL_TRIANGLES, 0, 36);
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
