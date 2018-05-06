#include "stdafx.h"
#include <iostream>

VkInstance VulkanHandler::CreateInstance()
{
	VkInstance instance;
	VkApplicationInfo appInfo = CreateApplicationInfo();
	VkInstanceCreateInfo instanceInfo = CreateInstanceInfo(&appInfo);
	const auto result = vkCreateInstance(&instanceInfo, nullptr, &instance);
	ErrorHandler::HandleError(result);
	return instance;
}

VkDevice VulkanHandler::CreateLogicalDevice(const VkInstance instance)
{
	uint32_t amountOfPhysicslDevices = 0;
	VkResult result = vkEnumeratePhysicalDevices(instance, &amountOfPhysicslDevices, nullptr);
	ErrorHandler::HandleError(result);
	
	VkPhysicalDevice* physicalDevices = new VkPhysicalDevice[amountOfPhysicslDevices];
	result = vkEnumeratePhysicalDevices(instance, &amountOfPhysicslDevices, physicalDevices);
	ErrorHandler::HandleError(result);

	for (uint32_t i = 0; i < amountOfPhysicslDevices; i++)
		PrintGraphicsCardStats(physicalDevices[i]);
	
	VkDeviceQueueCreateInfo queueInfo = CreateDeviceQueueInfo();
	VkPhysicalDeviceFeatures* features = new VkPhysicalDeviceFeatures();
	VkDeviceCreateInfo deviceInfo = CreateDeviceInfo(features, &queueInfo, 1);
	VkDevice device;
	result = vkCreateDevice(physicalDevices[0], &deviceInfo, nullptr, &device); //TODO pick best device
	ErrorHandler::HandleError(result);
	return device;
}

VkApplicationInfo VulkanHandler::CreateApplicationInfo()
{
	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = nullptr;
	appInfo.pApplicationName = "Vulkan Tutorial";
	appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.pEngineName = "Game engine";
	appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	return appInfo;
}

VkInstanceCreateInfo VulkanHandler::CreateInstanceInfo(VkApplicationInfo *appInfo)
{
	VkInstanceCreateInfo instanceInfo;
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = nullptr;
	instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo = appInfo;
	instanceInfo.enabledLayerCount = 0;
	instanceInfo.ppEnabledLayerNames = nullptr;
	instanceInfo.enabledExtensionCount = 0;
	instanceInfo.ppEnabledExtensionNames = nullptr;
	return instanceInfo;
}

VkDeviceQueueCreateInfo VulkanHandler::CreateDeviceQueueInfo()
{
	VkDeviceQueueCreateInfo deviceQueueInfo;
	deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueInfo.pNext = nullptr;
	deviceQueueInfo.flags = 0;
	deviceQueueInfo.queueFamilyIndex = 0;	// Use first family that has all abilities TODO pick best family
	deviceQueueInfo.queueCount = 4;			// How many queue to use from the selected family TODO pick right amount of queues
	deviceQueueInfo.pQueuePriorities = nullptr;
	return deviceQueueInfo;
}

VkDeviceCreateInfo VulkanHandler::CreateDeviceInfo(VkPhysicalDeviceFeatures *features, VkDeviceQueueCreateInfo* queueInfos, uint32_t queueInfosCount)
{
	VkDeviceCreateInfo deviceInfo;
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.pNext = nullptr;
	deviceInfo.flags = 0;
	deviceInfo.queueCreateInfoCount = queueInfosCount;
	deviceInfo.pQueueCreateInfos = queueInfos;
	deviceInfo.enabledLayerCount = 0;
	deviceInfo.ppEnabledLayerNames = nullptr;
	deviceInfo.enabledExtensionCount = 0;
	deviceInfo.ppEnabledExtensionNames = nullptr;
	deviceInfo.pEnabledFeatures = features;

	return deviceInfo;
}

void VulkanHandler::PrintGraphicsCardStats(VkPhysicalDevice &device)
{
	VkPhysicalDeviceProperties properties;
	vkGetPhysicalDeviceProperties(device, &properties);
	std::cout << "Device name: " << properties.deviceName << std::endl;
	ConsoleHandler::PrintVersion(properties.apiVersion);

	uint32_t amountQueueFamilies = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &amountQueueFamilies, nullptr);
	VkQueueFamilyProperties *familyProperties = new VkQueueFamilyProperties[amountQueueFamilies];
	vkGetPhysicalDeviceQueueFamilyProperties(device, &amountQueueFamilies, familyProperties);
	std::cout << "Amount of queue families: " << amountQueueFamilies << std::endl;
	for(uint32_t i = 0; i < amountQueueFamilies; i++)
	{
		std::cout << "\t" << "Queue family number: " << i << std::endl;
		std::cout << "\t\t" << "VK_Queue_Graphics_Bit: " << ((familyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) << std::endl;
		std::cout << "\t\t" << "VK_Queue_Compute_Bit: " << ((familyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT) != 0) << std::endl;
		std::cout << "\t\t" << "VK_Queue_Transfer_Bit: " << ((familyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0) << std::endl;
		std::cout << "\t\t" << "VK_Queue_Sparse_Binding_Bit: " << ((familyProperties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT) != 0) << std::endl;
		std::cout << "\t\t" << "Queue count: " << familyProperties[i].queueCount << std::endl;
		std::cout << std::endl;
	}
	std::cout << std::endl;
	delete[] familyProperties;
}
