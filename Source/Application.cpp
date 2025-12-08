#include <ostream>
#include <iostream>
#include "../Header/Application.h"
#include "../Header/Globals.h"
#include "../Header/ResourceManager.h"
#include "../Header/Renderer.h"
#include "../Header/Input.h"
#include "../Header/Util.h"
#include "../Header/Callbacks.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Application::Application()
    : window_(nullptr)
{}

Application::~Application() {
    if (window_) Shutdown();
}

bool Application::Init()
{
    if (!glfwInit()) {
        std::cerr << "glfwInit failed\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    window_ = glfwCreateWindow(mode->width, mode->height, "AirConditioner", monitor, NULL);
    if (!window_) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window_);

    // cursors
    remote = loadImageToCursor("Resources/remote.png");
    remoteDownPressed = loadImageToCursor("Resources/remote_down_pressed.png");
    remoteUpPressed = loadImageToCursor("Resources/remote_up_pressed.png");
    remotePowerPressed = loadImageToCursor("Resources/remote_power_pressed.png");
    if (remote) glfwSetCursor(window_, remote);

    if (glewInit() != GLEW_OK) {
        std::cerr << "glewInit failed\n";
        return false;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // load resources
    ResourceManager* rm = new ResourceManager();
    if (!rm->LoadAll(glfwGetVideoMode(glfwGetPrimaryMonitor()))) {
        std::cerr << "Failed to load resources\n";
        delete rm;
        return false;
    }

    renderer_.SetResources(rm);

    glfwSetWindowUserPointer(window_, rm);
	glfwSetMouseButtonCallback(window_, center_callback);
    return true;
}

void Application::Run()
{
    if (!window_) return;
    ResourceManager* rm = static_cast<ResourceManager*>(glfwGetWindowUserPointer(window_));
    if (!rm) return;

    while (!glfwWindowShouldClose(window_)) {
        double t0 = glfwGetTime();

        // flap movement update 
        if (isFlapMoving) {
            if ((fill == 0.0f && uLampPower == 0.0f) || (fill == 1.0f && uLampPower == 1.0f)) {
                isFlapMoving = false;
            } else {
                fill += (uLampPower == 1.0f) ? 0.001f : -0.001f;
				if (fill < 0.0f || fill > 1.0f) isFlapMoving = false;
            }
        }

        //water level update
        if (uLampPower == 1.0f and !isFlapMoving) {
            static double lastFillUpdate = 0.0;
            double now = glfwGetTime();
            if (lastFillUpdate == 0.0) lastFillUpdate = now;
            if (now - lastFillUpdate >= 1.0) {
                lastFillUpdate = now;
                const float step = 0.05f; 
                waterLevel += step;
                if (waterLevel >= 1.0f) {
                    uLampPower = 0.0f;
                    isFlapMoving = true;
					currentDigit1Screen1 = 3;
                    currentDigit2Screen1 = 5;
                }
            }
        }

		// temperature update
        if (!isFlapMoving && uLampPower >= 1.0f){
            if (isCold()) {
                static double lastFillUpdate = 0.0;
                double now = glfwGetTime();
                if (lastFillUpdate == 0.0) lastFillUpdate = now;
                if (now - lastFillUpdate >= 2.0) {
                    lastFillUpdate = now;
                    IncreaseTemperature(currentDigit1Screen2, currentDigit2Screen2);
                    CheckSymbol();
                }
            }

            if (isHot()) {
                static double lastFillUpdate = 0.0;
                double now = glfwGetTime();
                if (lastFillUpdate == 0.0) lastFillUpdate = now;
                if (now - lastFillUpdate >= 2.0) {
                    lastFillUpdate = now;
                    LowerTemperature(currentDigit1Screen2, currentDigit2Screen2);
                    CheckSymbol();
                }
            }
        }

        // input
        ProcessInput(window_);

        // render
        renderer_.RenderFrame(window_);

        glfwSwapBuffers(window_);
        glfwPollEvents();

        // simple frame limiter ~75Hz
        while (glfwGetTime() - t0 < 1.0 / 75.0) {}
    }
}

void Application::Shutdown()
{
    if (!window_) return;

    ResourceManager* rm = static_cast<ResourceManager*>(glfwGetWindowUserPointer(window_));
    if (rm) {
        rm->ReleaseAll();
        delete rm;
        glfwSetWindowUserPointer(window_, nullptr);
    }

    if (remote) { glfwDestroyCursor(remote); remote = nullptr; }
    if (remoteUpPressed) { glfwDestroyCursor(remoteUpPressed); remoteUpPressed = nullptr; }
    if (remoteDownPressed) { glfwDestroyCursor(remoteDownPressed); remoteDownPressed = nullptr; }
    if (remotePowerPressed) { glfwDestroyCursor(remotePowerPressed); remotePowerPressed = nullptr; }

    glfwDestroyWindow(window_);
    window_ = nullptr;
    glfwTerminate();
}