#include "Texture.h"

Texture::Texture(const char* path, int num) {

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path, &width, &height, &nrChannels, 0);

	if (num == -1) {
		for (int i = 0; i < 8; i++) {
			coords[i] = 0.0f;
		}
	}

	else if (num <= 4) {
		coords[0] = 0.25f * num;
		coords[1] = 1.0f;
		coords[2] = 0.25f * num;
		coords[3] = 0.5f;
		coords[4] = 0.25f * (num - 1);
		coords[5] = 0.5f;
		coords[6] = 0.25f * (num - 1);
		coords[7] = 1.0f;
	}
	else {
		coords[0] = 0.25f * (num - 4);
		coords[1] = 0.5f;
		coords[2] = 0.25f * (num - 4);
		coords[3] = 0.0f;
		coords[4] = 0.25f * (num - 5);
		coords[5] = 0.0f;
		coords[6] = 0.25f * (num - 5);
		coords[7] = 0.5f;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		//std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Texture::~Texture() {
}
