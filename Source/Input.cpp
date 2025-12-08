#include "../../Header/Input.h"
#include "../../Header/Globals.h"
#include <GLFW/glfw3.h>
#include "../Header/Rectangle/Rectangle.h"
#include <cstdio> // at top of file (for fprintf)

void CheckSymbol() {
    if (isHot()) currentSymbol = 0;
    else if (isCold()) currentSymbol = 2;
    else currentSymbol = 1;
}

bool isCold() {
    int wanted_temp = currentDigit1Screen1 * 10 + currentDigit2Screen1;
    int current_temp = currentDigit1Screen2 * 10 + currentDigit2Screen2;
    return wanted_temp > current_temp;
}

bool isHot() {
    int wanted_temp = currentDigit1Screen1 * 10 + currentDigit2Screen1;
    int current_temp = currentDigit1Screen2 * 10 + currentDigit2Screen2;
    return wanted_temp < current_temp;
}

void IncreaseTemperature(int& digit1, int& digit2) {
    if (uLampPower == 1.0f) {
        if (digit1 != 4 || digit2 != 10) {
            if (digit1 < 1) {
                digit2--;
                if (digit2 == 1) {
                    digit2 = 1;
                    digit1 = 1;
                }
            } else {
                digit2++;
                if (digit2 == 11) {
                    digit2 = 1;
                    digit1++;
                }
            }
        }
    }
}

void LowerTemperature(int& digit1, int& digit2) {
    if (uLampPower == 1.0f) {
        if (digit1 != 0 || digit2 != 10) {
            if (digit1 < 1) {
                digit2++;
                if (digit2 == 11) {
                    digit2 = 10;
                    digit1 = 0;
                }
            } else {
                digit2--;
                if (digit2 == 0) {
                    digit1--;
                    if (digit1 > 0)
                        digit2 = 10;
                    else
                        digit2 = 2;
                }
            }
        }
    }
}

void ProcessInput(GLFWwindow* window) {
    if (!window) return;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !upPressed) {
        if (remoteUpPressed) glfwSetCursor(window, remoteUpPressed);
        upPressed = true;
        IncreaseTemperature(currentDigit1Screen1, currentDigit2Screen1);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !downPressed) {
        if (remoteDownPressed) glfwSetCursor(window, remoteDownPressed);
        downPressed = true;
        LowerTemperature(currentDigit1Screen1, currentDigit2Screen1);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE && upPressed) {
        if (remote) glfwSetCursor(window, remote);
        upPressed = false;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE && downPressed) {
        if (remote) glfwSetCursor(window, remote);
        downPressed = false;
    }

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		waterLevel = 0.0f;
    }

    CheckSymbol();
}