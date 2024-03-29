#include <vulkan/vulkan.h>
#include <stdbool.h>

// picks a physical device
void pickPhysicalDevice(VkInstance *instance, VkPhysicalDevice *physicalDevice, VkSurfaceKHR surface);

extern const char *deviceExtensions;

extern const uint32_t numDeviceExtensions;
