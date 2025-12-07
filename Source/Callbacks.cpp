#include "../Header/Callbacks.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Header/Util.h"

void center_callback(GLFWwindow* window, int button, int action, int mods)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	
	bool inside = true;
	 
	float nx = (float)(xpos / width) * 2.0f - 1.0f;
	float ny = 1.0f - (float)(ypos / height) * 2.0f;
	if (nx < xc - r*3 || nx > xc + r*3 || ny < yc - r*3 || ny > yc + r*3) {
		inside = false;
	}

	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwSetCursor(window, remotePowerPressed);
		if (inside) {
			uLampPower = (uLampPower < 1.0f) ? 1.0f : 0.0f;
			useFill = true;
			isFlapMoving = true;
		}
	} 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		glfwSetCursor(window, remote);
	}
}
