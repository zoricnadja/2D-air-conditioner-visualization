#include "../../Header/DrawRectangle/Background.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../Header/Util.h"

unsigned backgroundTexture;
unsigned int bgVAO;
unsigned int bgVBO;

void initBackground(int width, int height) {
	float bgVertices[] = {
	   -1.0f,  1.0f, 0.0f, 1.0f,
	   -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, 1.0f, 1.0f
	};
	glGenVertexArrays(1, &bgVAO);
	glGenBuffers(1, &bgVBO);
	glBindVertexArray(bgVAO);
	glBindBuffer(GL_ARRAY_BUFFER, bgVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bgVertices), bgVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	backgroundTexture = loadImageToTexture("Resources/background.png");
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void drawBackground(unsigned int rectShader) {
	glUseProgram(rectShader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glBindVertexArray(bgVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void deleteBackground() {
	glDeleteVertexArrays(1, &bgVAO);
	glDeleteBuffers(1, &bgVBO);
	glDeleteTextures(1, &backgroundTexture);
}