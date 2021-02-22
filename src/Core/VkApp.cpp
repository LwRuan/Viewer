#include "VkApp.h"

void VkApp::run(){
    initWindow();
    initVulkan();
    mainLoop();
    cleanUp();
}

void VkApp::initWindow(){
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);//no OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow(WIDTH, HEIGHT, "VkViewer", nullptr, nullptr);
}

void VkApp::initVulkan(){

}

void VkApp::mainLoop(){
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();
    }
}

void VkApp::cleanUp(){
    glfwDestroyWindow(_window);
    glfwTerminate();
}