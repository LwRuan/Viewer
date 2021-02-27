#pragma once

#include "HelperFunc.h"
#include "Types.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <array>
#include <stdexcept>
#include <cstdlib>
#include <optional>

class VkApp
{
public:
    void run();

private:
    /************************struct*******************************/
    /*************************************************************/

    struct QueueFamilyIndices {
        //could be different queue family index
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct Vertex {
        Vector3f pos;
        Vector3f color;
        Vector2f texCoord;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions(){
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }
    };

    struct UniformBufferObject {
        alignas(16) Matrix4f model;
        alignas(16) Matrix4f view;
        alignas(16) Matrix4f proj;
    };

    /************************function*****************************/
    /*************************************************************/

    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanUp();

    void createInstance();
    void createSurface();
    void setupDebugMessenger();
    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, 
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
        const VkAllocationCallbacks* pAllocator, 
        VkDebugUtilsMessengerEXT* pDebugMessenger);
    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, 
        VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();

    void pickPhysicalDevice();
    //can these functions be moved to another class or namespace?
    bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    void createLogicalDevice();
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void createSwapChain();
    void createImageViews();

    void createGraphicsPipeline();
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void recreateSwapChain();//resize
    void cleanupSwapChain();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createDescriptorSetLayout();
    void updateUniformBuffer(uint32_t currentImage);
    void createDescriptorPool();
    void createDescriptorSets();
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, 
        VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void createTextureImage();
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout,
        VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void createTextureImageView();
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags asepctFlags);
    void createTextureSampler();
    void createDepthResources();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, 
        VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);


    void drawFrame();

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    /************************variable*****************************/
    /*************************************************************/
    //glfw window
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    GLFWwindow* _window;

    //debug
    const std::vector<const char*> _validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif
    VkDebugUtilsMessengerEXT _debugMessenger;
    std::vector<VkExtensionProperties> _extensions;

    const std::vector<const char*> _deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    std::vector<VkImage> _swapChainImages;
    VkFormat _swapChainImageFormat;
    VkExtent2D _swapChainExtent;
    std::vector<VkImageView> _swapChainImageViews;
    VkRenderPass _renderPass;
    VkDescriptorSetLayout _descriptorSetLayout;
    VkPipelineLayout _pipelineLayout;
    VkPipeline _graphicsPipeline;
    std::vector<VkFramebuffer> _swapChainFramebuffers;
    VkCommandPool _commandPool;
    std::vector<VkCommandBuffer> _commandBuffers;
    const int MAX_FRAMES_IN_FLIGHT = 2;
    std::vector<VkSemaphore> _imageAvailableSemaphores;
    std::vector<VkSemaphore> _renderFinishedSemaphores;
    std::vector<VkFence> _inFlightFences;
    std::vector<VkFence> _imagesInFlight;
    size_t _currentFrame = 0;

    VkImage _textureImage;
    VkImageView _textureImageView;
    VkSampler _textureSampler;
    VkDeviceMemory _textureImageMemory;

    VkImage _depthImage;
    VkDeviceMemory _depthImageMemory;
    VkImageView _depthImageView;

    VkInstance _instance;
    VkSurfaceKHR _surface;
    VkPhysicalDevice _physicalDevice;
    VkDevice _device;
    VkQueue _graphicsQueue;
    VkQueue _presentQueue;
    VkSwapchainKHR _swapChain;
    VkBuffer _vertexBuffer;
    VkDeviceMemory _vertexBufferMemory;
    VkBuffer _indexBuffer;
    VkDeviceMemory _indexBufferMemory;
    VkDescriptorPool _descriptorPool;
    std::vector<VkDescriptorSet> _descriptorSets;

    std::vector<VkBuffer> _uniformBuffers;
    std::vector<VkDeviceMemory> _uniformBuffersMemory;

    const std::vector<Vertex> _vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    };

    const std::vector<uint16_t> _indices = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4
    };


public:
    bool _framebufferResized = false;
};