cmake_minimum_required(VERSION 3.10)

set(BIN_NAME "VkViewer")

project(VkViewer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(Eigen3 CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)


add_subdirectory(${PROJECT_SOURCE_DIR}/src/Core)
include_directories(${PROJECT_SOURCE_DIR}/src/Core)

set(CMAKE_CXX_STANDARD 17)
add_executable(${BIN_NAME} src/main.cpp)
target_link_libraries(${BIN_NAME} Core)

target_link_libraries(${BIN_NAME} Eigen3::Eigen)
target_link_libraries(${BIN_NAME} glfw)
target_link_libraries(${BIN_NAME} Vulkan::Vulkan)