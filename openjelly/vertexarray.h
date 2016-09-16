#pragma once

#include <GL\glew.h>

class VertexArray {
public:
	GLuint _vao;
	GLuint _vbo;
	Shader* _shader;

	VertexArray(GLuint vbo, Shader* shader) : _vbo(vbo), _shader(shader) {
		glGenVertexArrays(1, &_vao);
	}

	void enableAttrib(GLuint num, GLuint count, GLuint stride) {
		glBindVertexArray(_vao);
		glVertexAttribPointer(num, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(stride * sizeof(GLfloat)));
		glEnableVertexAttribArray(num);
		glBindVertexArray(0);
	}

	void draw(GLuint pointCount) {
		_shader->use();
		glBindVertexArray(_vbo);
		glDrawArrays(GL_TRIANGLES, 0, pointCount);
		glBindVertexArray(0);
	}

private:
};
