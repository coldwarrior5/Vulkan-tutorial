#include "stdafx.h"
#include <ostream>
#include <iostream>

namespace ConsoleHandler
{
	void PrintVersion(uint32_t version)
	{
		std::cout << "Vulkan API version:  " << VK_VERSION_MAJOR(version) << "." << VK_VERSION_MINOR(version) << "." << VK_VERSION_PATCH(version) << std::endl;
	}
}
