#include "../../Header/Circle/Lamp.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../Header/Util.h"

void initCircle(float* vertices, size_t size, unsigned int& vao, unsigned int& vbo)
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void drawCircle(unsigned int shader, unsigned int& vao) {
	glUseProgram(shader);
	glUniform1f(glGetUniformLocation(shader, "uR"), uLampPower);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_SLICES + 2);
}

void deleteCircle(unsigned int& vao, unsigned int& vbo) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}