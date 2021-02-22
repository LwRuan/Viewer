#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class VkApp
{
public:
    void run();

private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanUp();

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    GLFWwindow* _window;
};