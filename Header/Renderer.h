#pragma once
#include "../Header/ResourceManager.h"
#include <GLFW/glfw3.h>

class Renderer {
public:
    Renderer() = default;
    ~Renderer() = default;

    void SetResources(ResourceManager* rm);

    void RenderFrame(GLFWwindow* window);

private:
    ResourceManager* rm_ = nullptr;
};