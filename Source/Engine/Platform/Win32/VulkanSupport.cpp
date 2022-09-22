#include <Engine/Platform/Win32/VulkanSupport.h>
#include <Engine/Platform/Platform.h>
#define DECLARE_VK_ENTRYPOINTS(Type,Func) Type Func = NULL;
	ENUM_VK_ENTRYPOINTS_ALL(DECLARE_VK_ENTRYPOINTS);
#undef DECLARE_VK_ENTRYPOINTS
namespace MeteorEngine
{
	void InitPlatformVulkan()
	{
		vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)Platform::GetDllFunction("vulkan-1.dll", "vkGetInstanceProcAddr");
		
		#define GET_VK_ENTRYPOINTS_DLL(Type,Func) Func = (Type)Platform::GetDllFunction("vulkan-1.dll", TEXT(#Func));
			ENUM_VK_ENTRYPOINTS_ALL(GET_VK_ENTRYPOINTS_DLL);
		#undef GET_GL_ENTRYPOINTS_DLL
	}
}