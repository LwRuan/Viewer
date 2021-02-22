#include "VkApp.h"

#include <Eigen/Dense>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

int main() {
    VkApp vkapp;
    try {
        vkapp.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}