find_package(Eigen3 CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
add_library(Core VkApp.h VkApp.cpp)
target_link_libraries(Core Eigen3::Eigen)
target_link_libraries(Core glfw)
target_link_libraries(Core Vulkan::Vulkan)
