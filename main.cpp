#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Eigen/Dense>

#include <iostream>

int main(){
    std::cout << Eigen::Vector3d::Ones().transpose() << std::endl;
    return 0;
}