﻿#include "stdafx.h"
#include <iostream>
int Start();

VkInstance instance;
VkDevice device;

int main()
{
	const int result = Start();
	system("pause");
    return result;
}

int Start()
{
	VulkanHandler vulkanHandler = VulkanHandler();
	instance = vulkanHandler.CreateInstance();
	device = vulkanHandler.CreateLogicalDevice(instance);

	return 0;
}

