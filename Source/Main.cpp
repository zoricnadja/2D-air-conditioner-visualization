#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <cmath> 
#include <algorithm> 
#include <iostream>
#include "../Header/Util.h"
#include "../Header/Callbacks.h"
#include "../Header/Rectangle/Rectangle.h"
#include "../Header/Circle/Lamp.h"

const int NUM_SLICES = 50;
const int NUM_OF_DIGITS = 10 + 1;
const int NUM_OF_SYMBOLS = 3;

GLFWcursor* remote;
GLFWcursor* remoteUpPressed;
GLFWcursor* remoteDownPressed;
GLFWcursor* remotePowerPressed;

bool upPressed = false;
bool downPressed = false;
float xc = -0.53f, yc = 0.59f, r = 0.0045f;
float uLampPower = 0.0f;
bool isFlapMoving = false;
//wanted temp
int currentDigit1Screen1 = 3;
int currentDigit2Screen1 = 5;
//current temp
int currentDigit1Screen2 = 4;
int currentDigit2Screen2 = 1;
int currentSymbol = 0;

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
       -0.45f, 0.25f, 1.0f, 0.0f,
       -0.45f, 1.1f, 1.0f, 1.0f
    };

    float flapVertices[] = {
       -0.915f, 0.62f, 0.0f, 1.0f,
       -0.91f,  0.585f, 0.0f, 0.0f,
       -0.54f,  0.585f, 1.0f, 0.0f,
       -0.535f, 0.62f, 1.0f, 1.0f
    };

    float screen1Vertices[] = {
       -0.91f,  0.72f, 0.0f, 1.0f,
       -0.91f,  0.685f, 0.0f, 0.0f,
       -0.85f,  0.685f, 1.0f, 0.0f,
       -0.85f,  0.72f, 1.0f, 1.0f
    };

    float screen1num1Vertices[] = {
       -0.91f,  0.72f, 0.0f, 1.0f,
       -0.91f,  0.685f, 0.0f, 0.0f,
       -0.895f,  0.685f, 1.0f, 0.0f,
       -0.895f,  0.72f, 1.0f, 1.0f
    };

    float screen1num2Vertices[] = {
       -0.895f,  0.72f, 0.0f, 1.0f,
       -0.895f,  0.685f, 0.0f, 0.0f,
       -0.88f,  0.685f, 1.0f, 0.0f,
       -0.88f,  0.72f, 1.0f, 1.0f
    };

    float screen1degreeVertices[] = {
       -0.88f, 0.72f, 0.0f, 1.0f,
       -0.88f, 0.685f, 0.0f, 0.0f,
       -0.865f, 0.685f, 1.0f, 0.0f,
       -0.865f, 0.72f, 1.0f, 1.0f
    };

    float screen1celsiusVertices[] = {
       -0.865f,  0.72f, 0.0f, 1.0f,
       -0.865f,  0.685f, 0.0f, 0.0f,
       -0.85f,  0.685f, 1.0f, 0.0f,
       -0.85f,  0.72f, 1.0f, 1.0f
    };

    float screen2Vertices[] = {
       -0.59f,  0.72f, 0.0f, 1.0f,
       -0.59f,  0.685f, 0.0f, 0.0f,
       -0.53f,  0.685f, 1.0f, 0.0f,
       -0.53f,  0.72f, 1.0f, 1.0f
    };
    
    float screen2num1Vertices[] = {
       -0.59f,  0.72f, 0.0f, 1.0f,
       -0.59f,  0.685f, 0.0f, 0.0f,
       -0.575f,  0.685f, 1.0f, 0.0f,
       -0.575f,  0.72f, 1.0f, 1.0f
    };

    float screen2num2Vertices[] = {
       -0.575f,  0.72f, 0.0f, 1.0f,
       -0.575f,  0.685f, 0.0f, 0.0f,
       -0.56f,  0.685f, 1.0f, 0.0f,
       -0.56f,  0.72f, 1.0f, 1.0f
	};

    float screen2degreeVertices[] = {
       -0.56f, 0.72f, 0.0f, 1.0f,
       -0.56f, 0.685f, 0.0f, 0.0f,
       -0.545f, 0.685f, 1.0f, 0.0f,
       -0.545f, 0.72f, 1.0f, 1.0f
	};

    float screen2celsiusVertices[] = {
       -0.545f,  0.72f, 0.0f, 1.0f,
       -0.545f,  0.685f, 0.0f, 0.0f,
       -0.53f,  0.685f, 1.0f, 0.0f,
       -0.53f,  0.72f, 1.0f, 1.0f
	};

    float screen3Vertices[] = {
       -0.64f,  0.72f, 0.0f, 1.0f,
       -0.64f,  0.685f, 0.0f, 0.0f,
       -0.605f,  0.685f, 1.0f, 0.0f,
       -0.605f,  0.72f, 1.0f, 1.0f
    };

    float lampVertices[(NUM_SLICES + 2) * 2];

    lampVertices[0] = xc;
    lampVertices[1] = yc;
    for (int i = 1; i < NUM_SLICES + 2; ++i) {
        float angle = i * 2 * M_PI / NUM_SLICES;
        lampVertices[i * 2] = cos(angle) * r + xc;
        lampVertices[i * 2 + 1] = sin(angle) * r + yc;
    }
	unsigned int bgVAO, bgVBO;
	unsigned int acVAO, acVBO;
	unsigned int flapVAO, flapVBO;
	unsigned int screen1VAO, screen1VBO;
	unsigned int screen2VAO, screen2VBO;
	unsigned int screen3VAO, screen3VBO;
	unsigned int screen1num1VAO, screen1num1VBO;
	unsigned int screen1num2VAO, screen1num2VBO;
	unsigned int screen1degreeVAO, screen1degreeVBO;
	unsigned int screen1celsiusVAO, screen1celsiusVBO;
	unsigned int screen2num1VAO, screen2num1VBO;
	unsigned int screen2num2VAO, screen2num2VBO;
	unsigned int screen2degreeVAO, screen2degreeVBO;
	unsigned int screen2celsiusVAO, screen2celsiusVBO;
	unsigned int screen3num1VAO, screen3num1VBO;
	unsigned int screen3num2VAO, screen3num2VBO;
	unsigned int screen3degreeVAO, screen3degreeVBO;
	unsigned int screen3celsiusVAO, screen3celsiusVBO;
	unsigned int lampVAO, lampVBO;
	initRectangles(mode->width, mode->height, bgVertices,sizeof(bgVertices), bgVAO, bgVBO);
	initRectangles(mode->width, mode->height, acVertices, sizeof(acVertices), acVAO, acVBO);
	initRectangles(mode->width, mode->height, flapVertices, sizeof(flapVertices), flapVAO, flapVBO);
	initRectangles(mode->width, mode->height, screen1Vertices, sizeof(screen1Vertices), screen1VAO, screen1VBO);
	initRectangles(mode->width, mode->height, screen1num1Vertices, sizeof(screen1num1Vertices), screen1num1VAO, screen1num1VBO);
	initRectangles(mode->width, mode->height, screen1num2Vertices, sizeof(screen1num2Vertices), screen1num2VAO, screen1num2VBO);
	initRectangles(mode->width, mode->height, screen1degreeVertices, sizeof(screen1degreeVertices), screen1degreeVAO, screen1degreeVBO);
	initRectangles(mode->width, mode->height, screen1celsiusVertices, sizeof(screen1celsiusVertices), screen1celsiusVAO, screen1celsiusVBO);
	initRectangles(mode->width, mode->height, screen2Vertices, sizeof(screen2Vertices), screen2VAO, screen2VBO);
	initRectangles(mode->width, mode->height, screen2num1Vertices, sizeof(screen2num1Vertices), screen2num1VAO, screen2num1VBO);
	initRectangles(mode->width, mode->height, screen2num2Vertices, sizeof(screen2num2Vertices), screen2num2VAO, screen2num2VBO);
	initRectangles(mode->width, mode->height, screen2degreeVertices, sizeof(screen2degreeVertices), screen2degreeVAO, screen2degreeVBO);
	initRectangles(mode->width, mode->height, screen2celsiusVertices, sizeof(screen2celsiusVertices), screen2celsiusVAO, screen2celsiusVBO);
	initRectangles(mode->width, mode->height, screen3Vertices, sizeof(screen3Vertices), screen3VAO, screen3VBO);
    initCircle(lampVertices, sizeof(lampVertices), lampVAO, lampVBO);
    unsigned int bgTexture = loadTexture("Resources/background.png");
    unsigned int acTexture = loadTexture("Resources/air_conditioner.png");
	unsigned int flapTexture = loadTexture("Resources/air_vent_grill.png");
	unsigned int screenTexture = loadTexture("Resources/flap.jpeg");
	unsigned int lightGreyTexture = loadTexture("Resources/light_grey.jpg");
	unsigned int darkGreyTexture = loadTexture("Resources/dark_grey.png");
    unsigned int numberTextures[NUM_OF_DIGITS];
	numberTextures[0] = loadTexture("Resources/minus.png");
	numberTextures[1] = loadTexture("Resources/0.png");
	numberTextures[2] = loadTexture("Resources/1.png");
	numberTextures[3] = loadTexture("Resources/2.png");
	numberTextures[4] = loadTexture("Resources/3.png");
	numberTextures[5] = loadTexture("Resources/4.png");
	numberTextures[6] = loadTexture("Resources/5.png");
	numberTextures[7] = loadTexture("Resources/6.png");
	numberTextures[8] = loadTexture("Resources/7.png");
	numberTextures[9] = loadTexture("Resources/8.png");
	numberTextures[10] = loadTexture("Resources/9.png");
    unsigned int symbolTextures[NUM_OF_SYMBOLS];
	symbolTextures[0] = loadTexture("Resources/flake.png");
	symbolTextures[1] = loadTexture("Resources/done.png");
	symbolTextures[2] = loadTexture("Resources/fire.png");
	unsigned int degreeTexture = loadTexture("Resources/degree.png");
	unsigned int celsiusTexture = loadTexture("Resources/celsius.png");

    unsigned int rectShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
	unsigned int circleShader = createShader("Shaders/circle.vert", "Shaders/circle.frag");
    glUseProgram(rectShader);
    glUniform1i(glGetUniformLocation(rectShader, "uTex"), 0);
    glClearColor(0.5f, 0.6f, 1.0f, 1.0f);

    while (!glfwWindowShouldClose(window))
    {
        double initFrameTime = glfwGetTime();

        if (isFlapMoving) {
            if (fill == 0.0f && !uLampPower || fill == 1.0f && uLampPower)
                isFlapMoving = false;
            else
                fill += (uLampPower == 1.0f) ? 0.001f : -0.001f;
        }
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            break;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS and !upPressed) {
            glfwSetCursor(window, remoteUpPressed);
            upPressed = true;
            if (uLampPower == 1.0f) {
                if (currentDigit1Screen1 != 4 || currentDigit2Screen1 != 10) {
                    if (currentDigit1Screen1 < 1) {
                        currentDigit2Screen1--;
                        if (currentDigit2Screen1 == 1) {
                            currentDigit2Screen1 = 1;
                            currentDigit1Screen1 = 1;
                        }
                    }
                    else {
                        currentDigit2Screen1++;
                        if (currentDigit2Screen1 == 11) {
                            currentDigit2Screen1 = 1;
                            currentDigit1Screen1++;
                        }
                    }
                }
            }
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS and !downPressed) {
            glfwSetCursor(window, remoteDownPressed);
            downPressed = true;

            if (uLampPower == 1.0f) {
                if (currentDigit1Screen1 != 0 || currentDigit2Screen1 != 10) {
                    if (currentDigit1Screen1 < 1) {
                        currentDigit2Screen1++;
                        if (currentDigit2Screen1 == 11) {
                            currentDigit2Screen1 = 10;
                            currentDigit1Screen1 = 0;
                        }
                    }
                    else {
                        currentDigit2Screen1--;
                        if (currentDigit2Screen1 == 0) {
                            currentDigit1Screen1--;
                            if (currentDigit1Screen1 > 0)
                                currentDigit2Screen1 = 10;
                            else
                                currentDigit2Screen1 = 2;
                        }
                    }
                }
            }
        }
        if (currentDigit1Screen1 > currentDigit1Screen2)
            currentSymbol = 2;
        else if (currentDigit1Screen1 < currentDigit1Screen2)
            currentSymbol = 0;
        else {
            if (currentDigit2Screen1 == currentDigit2Screen2)
				currentSymbol = 1;
            else if (currentDigit2Screen1 > currentDigit2Screen2)
                currentSymbol = 2;
            else
				currentSymbol = 0;
        }
    
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE and upPressed) {
            glfwSetCursor(window, remote);
            upPressed = false;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE and downPressed) {
            downPressed = false;
            glfwSetCursor(window, remote);
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(rectShader);
        useFill = false;
        drawRectangles(rectShader, bgTexture, bgVAO);
        drawRectangles(rectShader, acTexture, acVAO);
		if (uLampPower == 1.0f) {
            drawRectangles(rectShader, lightGreyTexture, screen1VAO);
			drawRectangles(rectShader, lightGreyTexture, screen2VAO);
            drawRectangles(rectShader, numberTextures[currentDigit1Screen1], screen1num1VAO);
            drawRectangles(rectShader, numberTextures[currentDigit2Screen1], screen1num2VAO);
            drawRectangles(rectShader, degreeTexture, screen1degreeVAO);
            drawRectangles(rectShader, celsiusTexture, screen1celsiusVAO);
            drawRectangles(rectShader, numberTextures[currentDigit1Screen2], screen2num1VAO);
            drawRectangles(rectShader, numberTextures[currentDigit2Screen2], screen2num2VAO);
            drawRectangles(rectShader, degreeTexture, screen2degreeVAO);
            drawRectangles(rectShader, celsiusTexture, screen2celsiusVAO);
			drawRectangles(rectShader, symbolTextures[currentSymbol], screen3VAO);
        }
        else {
            drawRectangles(rectShader, darkGreyTexture, screen1VAO);
            drawRectangles(rectShader, darkGreyTexture, screen2VAO);
		    drawRectangles(rectShader, darkGreyTexture, screen3VAO);
        }
        
		useFill = true;
        drawRectangles(rectShader, flapTexture, flapVAO);
		drawCircle(circleShader, lampVAO);
        glfwSwapBuffers(window);
        glfwPollEvents();
        while (glfwGetTime() - initFrameTime < 1 / 75.0) {}

    }

	deleteRectangles(bgVAO, bgVBO, bgTexture);
    deleteRectangles(acVAO, acVBO, acTexture);
    deleteRectangles(flapVAO, flapVBO, flapTexture);
	deleteRectangles(screen1VAO, screen1VBO, screenTexture);
	deleteRectangles(screen1num1VAO, screen1num1VBO, numberTextures[currentDigit1Screen1]);
	deleteRectangles(screen1num2VAO, screen1num2VBO, numberTextures[currentDigit2Screen1]);
	deleteRectangles(screen1degreeVAO, screen1degreeVBO, degreeTexture);
	deleteRectangles(screen1celsiusVAO, screen1celsiusVBO, celsiusTexture);
	deleteRectangles(screen2VAO, screen2VBO, screenTexture);
	deleteRectangles(screen2num1VAO, screen2num1VBO, numberTextures[currentDigit1Screen2]);
	deleteRectangles(screen2num2VAO, screen2num2VBO, numberTextures[currentDigit2Screen2]);
	deleteRectangles(screen2degreeVAO, screen2degreeVBO, degreeTexture);
	deleteRectangles(screen2celsiusVAO, screen2celsiusVBO, celsiusTexture);
	deleteRectangles(screen3VAO, screen3VBO, symbolTextures[currentSymbol]);
	deleteCircle(lampVAO, lampVBO);
	glDeleteProgram(rectShader);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}