#include <Engine/Render/Pipeline.h>
#include <Engine/Render/Vulkan/VkPipeline.h>
namespace MeteorEngine
{

	Pipeline* Pipeline::Create(const PipelineInfo& info)
	{
		return new VulkanPipeline(info);
	}
}