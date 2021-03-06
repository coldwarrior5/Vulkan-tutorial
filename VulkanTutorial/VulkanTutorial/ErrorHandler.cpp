#include "stdafx.h"
#include <signal.h>

namespace ErrorHandler
{
	void HandleError(const VkResult result)
	{
		switch (result) { 
			case VK_SUCCESS: break;
			case VK_NOT_READY:
			case VK_TIMEOUT:
			case VK_EVENT_SET:
			case VK_EVENT_RESET:
			case VK_INCOMPLETE:
			case VK_ERROR_OUT_OF_HOST_MEMORY:
			case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			case VK_ERROR_INITIALIZATION_FAILED:
			case VK_ERROR_DEVICE_LOST:
			case VK_ERROR_MEMORY_MAP_FAILED:
			case VK_ERROR_LAYER_NOT_PRESENT:
			case VK_ERROR_EXTENSION_NOT_PRESENT:
			case VK_ERROR_FEATURE_NOT_PRESENT:
			case VK_ERROR_INCOMPATIBLE_DRIVER:
			case VK_ERROR_TOO_MANY_OBJECTS:
			case VK_ERROR_FORMAT_NOT_SUPPORTED:
			case VK_ERROR_FRAGMENTED_POOL:
			case VK_ERROR_SURFACE_LOST_KHR:
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
			case VK_SUBOPTIMAL_KHR:
			case VK_ERROR_OUT_OF_DATE_KHR:
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
			case VK_ERROR_VALIDATION_FAILED_EXT:
			case VK_ERROR_INVALID_SHADER_NV:
			case VK_ERROR_OUT_OF_POOL_MEMORY_KHR:
			case VK_RESULT_RANGE_SIZE:
			case VK_RESULT_MAX_ENUM:
				#ifdef _MSC_VER
				__debugbreak();
				#else
				raise(SIGTRAP);
				#endif
				break;
			default: ; 
		}
	}
}
