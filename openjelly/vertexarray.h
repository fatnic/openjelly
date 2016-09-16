#pragma once

#include <GL\glew.h>

class VertexArray {
public:
	GLuint _vao;
	GLuint _vbo;

	VertexArray(GLuint vbo) : _vbo(vbo) {
		glGenVertexArrays(1, &_vao);
	}

	void enableAttrib(GLuint num, GLuint count, GLuint stride) {
		glBindVertexArray(_vao);
		glVertexAttribPointer(num, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(stride * sizeof(GLfloat)));
		glEnableVertexAttribArray(num);
		glBindVertexArray(0);
	}

	void draw(GLuint pointCount) {
		glBindVertexArray(_vbo);
		glDrawArrays(GL_TRIANGLES, 0, pointCount);
		glBindVertexArray(0);
	}

private:
};
