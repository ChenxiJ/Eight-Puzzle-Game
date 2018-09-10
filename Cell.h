#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Texture.h"
#pragma once

class Cell {
public:
	Cell(float x, float y, float z, float cell_size, Texture texture);
	~Cell();
	GLuint VAO;
private:
	GLfloat vertices[20];
	GLint indices[6];
	GLuint EBO;
	GLuint VBO;
};

