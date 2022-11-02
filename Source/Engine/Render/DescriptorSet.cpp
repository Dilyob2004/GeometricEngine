#include <Engine/Render/DescriptorSet.h>
#include <Engine/Render/Vulkan/VkDescriptorSet.h>

namespace MeteorEngine
{
	DescriptorSet* DescriptorSet::Create(const DescriptorInfo& info)
	{
		return new VulkanDescriptorSet(info);
	}
}