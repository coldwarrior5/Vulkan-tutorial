#pragma once
#include "vulkan/vulkan.h"

class VulkanHandler
{
public:
	static VkInstance CreateInstance();
	static VkDevice CreateLogicalDevice(const VkInstance instance);
private:
	static VkApplicationInfo CreateApplicationInfo();
	static VkInstanceCreateInfo CreateInstanceInfo(VkApplicationInfo *appInfo);
	static VkDeviceQueueCreateInfo CreateDeviceQueueInfo();
	static VkDeviceCreateInfo CreateDeviceInfo(VkPhysicalDeviceFeatures *features, VkDeviceQueueCreateInfo *queueInfos, uint32_t queueInfosCount);
	static void PrintGraphicsCardStats(VkPhysicalDevice &device);
};
