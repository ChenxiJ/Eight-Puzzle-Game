#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <vector>
#include "Cell.h"
#include "stb_image.h"
#include "PuzzleSolver.h"
#include <chrono>
#include <thread>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow(800, 800, "8-Puzzle Game", NULL, NULL);
	if (window == NULL) {
		std::cout << "Window creation failed" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 800);

	std::cout << "Please give the initial order of the numbers, -1 for the empty cell." << std::endl;
	int puzzle[9];
	for (int i = 0; i < 9; i++) {
		std::cin >> puzzle[i];
	}

	std::vector<int> moves;
	PuzzleSolver puzzleSolver;

	puzzleSolver.solve(puzzle, moves);
	std::reverse(moves.begin(), moves.end());

	int emptyCellIndex = -1;
	for (int i = 0; i < 9; i++) {
		if (puzzle[i] == -1) {
			emptyCellIndex = i;
		}
	}

	int * puzzleState = puzzle;
	std::vector<Texture> textures;
	for (int i = 0; i < 9; i++) {
		Texture texture("c:/users/chenxi/desktop/numbers.png", puzzle[i]);
		textures.push_back(texture);
	}
	int order[9] = { 6,3,0,7,4,1,8,5,2 };
	std::vector<Cell> cells;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Cell cell(-0.25f + i * 0.45f, -0.25f + j * 0.45f, 0.0f, 0.4f, textures[order[j + 3 * i]]);
			cells.push_back(cell);
		}
	}

	const GLchar *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexCoord;\n"
		"out vec2 TexCoord;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"	TexCoord = aTexCoord;\n"
		"}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const GLchar *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec2 TexCoord;\n"
		"uniform sampler2D ourTexture;\n"
		"void main()\n"
		"{\n"
		"   FragColor = texture(ourTexture, TexCoord);\n"
		"}\n\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	int movesCount = 0;
	glClearColor(0.0f, 0.1f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);

		textures.clear();
		for (int i = 0; i < 9; i++) {
			Texture texture("numbers.jpg", puzzleState[i]);
			textures.push_back(texture);
		}

		cells.clear();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				Cell cell(-0.25f + i * 0.45f, -0.25f + j * 0.45f, 0.0f, 0.4f, textures[order[j + 3 * i]]);
				cells.push_back(cell);
			}
		}

		for (int i = 0; i < cells.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, textures[i].texture);
			glBindVertexArray(cells[i].VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		glBindVertexArray(0);

		if (movesCount < moves.size()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			int *newState = puzzleSolver.move(moves.at(movesCount), puzzleState, emptyCellIndex);
			emptyCellIndex += moves.at(movesCount);
			puzzleState = newState;
			movesCount++;
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
