#ifndef VKPIPELINE_H
#define VKPIPELINE_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/CommandBuffer.h>
#include <Engine/Render/Vulkan/VkRenderPass.h>
#include <Engine/Render/Vulkan/VkFrameBuffer.h>
namespace MeteorEngine
{
	struct PipelineInfo
	{
		bool SwapChainTarget = false;
		bool ClearTargets		= false;

		Texture* ColorTargets[10];
		Texture* DepthTarget = NULL;
		float clearColor[4] = {};
	};
	class METEOR_API VulkanPipeline
	{
	public:
		VulkanPipeline();
		VulkanPipeline(const PipelineInfo&);
		~VulkanPipeline();
		void Begin(CommandBuffer*, u32 layer);
		void End(CommandBuffer*);

		void PreInit();
		void TransitionBackbuffers();
	private:
		std::vector<VulkanFrameBuffer*> m_FrameBuffer;
		RenderPass* m_RenderPass;
		PipelineInfo m_PipelineInfo;
	};
}
#endif // !VKPIPELINE_H
