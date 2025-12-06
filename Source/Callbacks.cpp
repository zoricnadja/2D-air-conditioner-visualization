#include "../Header/Callbacks.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Header/Util.h"


void center_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		
		glfwSetCursor(window, remotePowerPressed);
	} 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		glfwSetCursor(window, remote);
	}
}
