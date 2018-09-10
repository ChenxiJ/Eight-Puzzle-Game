#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "stb_image.h"
#pragma once

class Texture {
public:
	Texture(const char* path, int num);
	~Texture();
	GLfloat coords[8];
	GLuint texture;

private:
	int width, height, nrChannels;
	stbi_uc *data;
};


