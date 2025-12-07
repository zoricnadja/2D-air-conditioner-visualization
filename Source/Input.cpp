#include "../../Header/Input.h"
#include "../../Header/Globals.h"
#include <GLFW/glfw3.h>

void CheckSymbol() {
    int wanted_temp = currentDigit1Screen1 * 10 + currentDigit2Screen1;
    int current_temp = currentDigit1Screen2 * 10 + currentDigit2Screen2;
    if (wanted_temp < current_temp) currentSymbol = 0;
    else if (wanted_temp > current_temp) currentSymbol = 2;
    else currentSymbol = 1;
}

void IncreaseTemperature() {
    if (uLampPower == 1.0f) {
        if (currentDigit1Screen1 != 4 || currentDigit2Screen1 != 10) {
            if (currentDigit1Screen1 < 1) {
                currentDigit2Screen1--;
                if (currentDigit2Screen1 == 1) {
                    currentDigit2Screen1 = 1;
                    currentDigit1Screen1 = 1;
                }
            } else {
                currentDigit2Screen1++;
                if (currentDigit2Screen1 == 11) {
                    currentDigit2Screen1 = 1;
                    currentDigit1Screen1++;
                }
            }
        }
    }
}

void LowerTemperature() {
    if (uLampPower == 1.0f) {
        if (currentDigit1Screen1 != 0 || currentDigit2Screen1 != 10) {
            if (currentDigit1Screen1 < 1) {
                currentDigit2Screen1++;
                if (currentDigit2Screen1 == 11) {
                    currentDigit2Screen1 = 10;
                    currentDigit1Screen1 = 0;
                }
            } else {
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

void ProcessInput(GLFWwindow* window) {
    if (!window) return;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !upPressed) {
        if (remoteUpPressed) glfwSetCursor(window, remoteUpPressed);
        upPressed = true;
        IncreaseTemperature();
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !downPressed) {
        if (remoteDownPressed) glfwSetCursor(window, remoteDownPressed);
        downPressed = true;
        LowerTemperature();
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE && upPressed) {
        if (remote) glfwSetCursor(window, remote);
        upPressed = false;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE && downPressed) {
        if (remote) glfwSetCursor(window, remote);
        downPressed = false;
    }

    CheckSymbol();
}