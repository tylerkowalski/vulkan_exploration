#include "physicalDevice.h"
#include <vulkan/vulkan.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

struct QueueFamilyIndices {
    uint32_t graphicsFamily;
    bool graphicsFamilyFound;
};

typedef struct QueueFamilyIndices QueueFamilyIndices;

static bool isComplete(struct QueueFamilyIndices indices) {
    if (indices.graphicsFamilyFound) {
        return true;
    }
    else {
        return false;
    }
}

static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;
    indices.graphicsFamilyFound = false;
    
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);
    VkQueueFamilyProperties *queueFamilies = malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);
    
    for (int i = 0; i < queueFamilyCount; ++i) {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
            indices.graphicsFamilyFound = true;
        }
        if (isComplete(indices)) {
            break;
        }
    }
    free(queueFamilies);
    return indices;
}

static bool isDeviceSuitable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = findQueueFamilies(device);
    return isComplete(indices);
}

void pickPhysicalDevice(VkInstance *instance, VkPhysicalDevice *physicalDevice) {

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(*instance, &deviceCount, NULL);
    
    assert(deviceCount > 0 && "failed to find GPUs with Vulkan support");
    
    VkPhysicalDevice *devices = malloc(deviceCount * sizeof(VkPhysicalDevice));
    vkEnumeratePhysicalDevices(*instance, &deviceCount, devices);
    
    bool foundSuitableDevice = false;
    for (int i = 0; i < deviceCount; ++i) {
        if (isDeviceSuitable(devices[i])) {
            *physicalDevice = devices[i];
            foundSuitableDevice = true;
            break;
        }
    }
    free(devices);
    assert(foundSuitableDevice && "failed to find suitable GPU");
}
