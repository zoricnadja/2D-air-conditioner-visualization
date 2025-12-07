#include "../../Header/Rectangle/Background.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../Header/Util.h"

float fill = 0.0f;
bool useFill = false;

void initRectangles(int width, int height, float* vertices, size_t size, unsigned int& vao, unsigned int& vbo)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

unsigned int loadTexture(const char* path) {
	unsigned int texture = loadImageToTexture(path);
	glBindTexture(GL_TEXTURE_2D, texture);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return texture;
}

void drawRectangles(unsigned int shader, unsigned int texture, unsigned int& vao) {
	glUseProgram(shader);

	glUniform1f(glGetUniformLocation(shader, "uFill"), fill);
	glUniform1f(glGetUniformLocation(shader, "uUseFill"), useFill);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void deleteRectangles(unsigned int& vao, unsigned int& vbo, unsigned int texture) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteTextures(1, &texture);
}