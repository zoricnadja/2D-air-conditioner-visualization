#pragma once
#include <GL/glew.h>

#include <GLFW/glfw3.h>

class Application
{
public:
    Application();
    ~Application();

    // initialize window, GL, resources
    bool Init();

    // run main loop (blocks until window close)
    void Run();

    // cleanup resources
    void Shutdown();

private:
    GLFWwindow* window_;
};