#pragma once

#include <GL\glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture {
public:
	GLuint id;

	Texture(const char* filename) {
		int tW, tH, tC;
		unsigned char* texImage = stbi_load(filename, &tW, &tH, &tC, STBI_rgb);
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tW, tH, 0, GL_RGB, GL_UNSIGNED_BYTE, texImage);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(texImage);
	}
};
