#include "Cell.h"

Cell::Cell(float x, float y, float z, float cell_size, Texture texture) {
	vertices[0] = x;
	vertices[1] = y;
	vertices[2] = 0.0f;
	vertices[3] = texture.coords[0];
	vertices[4] = texture.coords[1];

	vertices[5] = x;
	vertices[6] = y - cell_size;
	vertices[7] = 0.0f;
	vertices[8] = texture.coords[2];
	vertices[9] = texture.coords[3];

	vertices[10] = x - cell_size;
	vertices[11] = y - cell_size;
	vertices[12] = 0.0f;
	vertices[13] = texture.coords[4];
	vertices[14] = texture.coords[5];

	vertices[15] = x - cell_size;
	vertices[16] = y;
	vertices[17] = 0.0f;
	vertices[18] = texture.coords[6];
	vertices[19] = texture.coords[7];

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

Cell::~Cell() {
}
