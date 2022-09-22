#ifndef VK_H
#define VK_H



#include <Engine/Platform/Win32/VulkanSupport.h>
#define VK_CHECK(result, name) \
		if (result != VK_SUCCESS) \
		{ \
			LOG("Vulkan Error: "); LOGLN(name);\
			return; \
		} 

#endif // !VK_H
