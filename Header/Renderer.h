#pragma once
#include "../Header/ResourceManager.h"
#include <GLFW/glfw3.h>

class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    // attach resource manager (must be loaded)
    void SetResources(ResourceManager* rm);

    // render one frame
    void RenderFrame(GLFWwindow* window);

private:
    ResourceManager* rm_ = nullptr;
};