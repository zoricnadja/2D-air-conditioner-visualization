#pragma once
#include <array>
#include <GL/glew.h>
#include <cstddef>
#include <GLFW/glfw3.h> 

constexpr int NUM_OF_DIGITS = 11;
constexpr int NUM_OF_SYMBOLS = 3;

struct ResourceHandles {
    unsigned int bgVAO = 0, bgVBO = 0;
    unsigned int acVAO = 0, acVBO = 0;
    unsigned int flapVAO = 0, flapVBO = 0;
    unsigned int screen1VAO = 0, screen1VBO = 0;
    unsigned int screen2VAO = 0, screen2VBO = 0;
    unsigned int screen3VAO = 0, screen3VBO = 0;
    unsigned int screen1num1VAO = 0, screen1num1VBO = 0;
    unsigned int screen1num2VAO = 0, screen1num2VBO = 0;
    unsigned int screen1degreeVAO = 0, screen1degreeVBO = 0;
    unsigned int screen1celsiusVAO = 0, screen1celsiusVBO = 0;
    unsigned int screen2num1VAO = 0, screen2num1VBO = 0;
    unsigned int screen2num2VAO = 0, screen2num2VBO = 0;
    unsigned int screen2degreeVAO = 0, screen2degreeVBO = 0;
    unsigned int screen2celsiusVAO = 0, screen2celsiusVBO = 0;
    unsigned int waterVAO = 0, waterVBO = 0;
    unsigned int lampVAO = 0, lampVBO = 0;

    unsigned int rectShader = 0;
    unsigned int circleShader = 0;

    unsigned int bgTexture = 0;
    unsigned int acTexture = 0;
    unsigned int flapTexture = 0;
    unsigned int screenTexture = 0;
    unsigned int lightGreyTexture = 0;
    unsigned int darkGreyTexture = 0;
    unsigned int degreeTexture = 0;
    unsigned int celsiusTexture = 0;

    unsigned int waterTexture = 0;

    unsigned int nameVAO = 0, nameVBO = 0;
    unsigned int nameTexture = 0;

    std::array<unsigned int, NUM_OF_DIGITS> numberTextures{};
    std::array<unsigned int, NUM_OF_SYMBOLS> symbolTextures{};
};

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager();

    // Load all resources used by the scene. Returns true on success.
    bool LoadAll(const GLFWvidmode* mode);

    // Access loaded handles
    ResourceHandles& Get() { return resources_; }

    void ReleaseAll();

private:
    ResourceHandles resources_;
};