#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <cmath> // za pi
#include <algorithm> // za max()
#include <iostream>
#include "../Header/Util.h"
#include "../Header/Callbacks.h"
#include "../Header/Rectangle/Rectangle.h"
#include "../Header/Circle/Lamp.h"

const int NUM_SLICES = 50;

// Main fajl funkcija sa osnovnim komponentama OpenGL programa

// Projekat je dozvoljeno pisati počevši od ovog kostura
// Toplo se preporučuje razdvajanje koda po fajlovima (i eventualno potfolderima) !!!
// Srećan rad!
GLFWcursor* remote;
GLFWcursor* remoteUpPressed;
GLFWcursor* remoteDownPressed;
GLFWcursor* remotePowerPressed;

bool upPressed = false;
bool downPressed = false;
float uLampPower = 0.0f;
float xc, yc, r;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "AirConditioner", monitor, NULL);
    if (window == NULL) return endProgram("Failed to create the window.");
    glfwMakeContextCurrent(window);
    //glfwSetKeyCallback(window, squish_callback);
    glfwSetMouseButtonCallback(window, center_callback);

    remote = loadImageToCursor("Resources/remote.png");
    remoteDownPressed = loadImageToCursor("Resources/remote_down_pressed.png");
    remoteUpPressed = loadImageToCursor("Resources/remote_up_pressed.png");
    remotePowerPressed = loadImageToCursor("Resources/remote_power_pressed.png");
    
    glfwSetCursor(window, remote);

    if (glewInit() != GLEW_OK) return endProgram("GLEW nije uspeo da se inicijalizuje.");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    float bgVertices[] = {
       -1.0f,  1.0f, 0.0f, 1.0f,
       -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f
    };
    float acVertices[] = {
       -1.0f,  1.1f, 0.0f, 1.0f,
       -1.0f,  0.25f, 0.0f, 0.0f,
       -0.45f,  0.25f, 1.0f, 0.0f,
       -0.45f,  1.1f, 1.0f, 1.0f
    };

    float lampVertices[(NUM_SLICES + 2) * 2];

    xc = -0.53f, yc = 0.59f, r = 0.0045f;
    lampVertices[0] = xc;
    lampVertices[1] = yc;
    for (int i = 1; i < NUM_SLICES + 2; ++i) {
        float angle = i * 2 * M_PI / NUM_SLICES;
        lampVertices[i * 2] = cos(angle) * r + xc;
        lampVertices[i * 2 + 1] = sin(angle) * r + yc;
    }
	unsigned int bgVAO, bgVBO;
	unsigned int acVAO, acVBO;
	unsigned int lampVAO, lampVBO;
	initRectangles(mode->width, mode->height, bgVertices,sizeof(bgVertices), bgVAO, bgVBO);
	initRectangles(mode->width, mode->height, acVertices, sizeof(acVertices), acVAO, acVBO);
	initCircle(lampVertices, sizeof(lampVertices), lampVAO, lampVBO);
    unsigned int bgTexture = loadTexture("Resources/background.png");
    unsigned int acTexture = loadTexture("Resources/air_conditioner.png");
    unsigned int rectShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
	unsigned int circleShader = createShader("Shaders/circle.vert", "Shaders/circle.frag");
    glUseProgram(rectShader);
    glUniform1i(glGetUniformLocation(rectShader, "uTex"), 0);
    glClearColor(0.5f, 0.6f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        double initFrameTime = glfwGetTime();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            break;
        }
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS and !upPressed) {
            glfwSetCursor(window, remoteUpPressed);
			upPressed = true;
        } 
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS and !downPressed) {
            glfwSetCursor(window, remoteDownPressed);
			downPressed = true;
        }
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE and upPressed) {
            glfwSetCursor(window, remote);
			upPressed = false;
        } 
        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE and downPressed) {
			downPressed = false;
            glfwSetCursor(window, remote);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(rectShader);
        drawRectangles(rectShader, bgTexture, bgVAO);
        drawRectangles(rectShader, acTexture, acVAO);
		drawCircle(circleShader, lampVAO);
        glfwSwapBuffers(window);
        glfwPollEvents();
        while (glfwGetTime() - initFrameTime < 1 / 75.0) {}

    }

	deleteRectangles(bgVAO, bgVBO, bgTexture);
    deleteRectangles(acVAO, acVBO, acTexture);
	deleteCircle(lampVAO, lampVBO);
	glDeleteProgram(rectShader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}