#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <cmath> // za pi
#include <algorithm> // za max()
#include <iostream>
#include "../Header/Util.h"
#include "../Header/Callbacks.h"

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

    glClearColor(0.2f, 0.8f, 0.6f, 1.0f);

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

        glfwSwapBuffers(window);
        glfwPollEvents();
        while (glfwGetTime() - initFrameTime < 1 / 75.0) {}

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}