#ifndef VKPIPELINE_H
#define VKPIPELINE_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/RenderPass.h>
#include <Engine/Render/Vulkan/VkFrameBuffer.h>
#include <Engine/Render/Pipeline.h>
namespace MeteorEngine
{
	class METEOR_API VulkanPipeline : public Pipeline
	{
	public:
		VulkanPipeline();
		VulkanPipeline(const PipelineInfo&);
		virtual ~VulkanPipeline();
		virtual void Begin(CommandBuffer*) override;
		virtual void End(CommandBuffer*) override;

		virtual void ClearRenderTargets(CommandBuffer* commandBuffer) override;
		virtual Shader* GetShader() override { return m_Shader; }
		void PreInit();
		void TransitionBackbuffers();
		VkPipelineLayout GetPipelineLayout() const{ return m_PipelineLayout; }
	private:
		Shader* m_Shader;
		RenderPass* m_RenderPass;
		PipelineInfo m_PipelineInfo;
		std::vector< FrameBuffer* > m_FrameBuffer;


		VkPipelineLayout m_PipelineLayout{0};
		VkPipeline m_Pipeline{0};
		bool m_DepthBiasEnabled;
		float m_DepthBiasConstant;
		float m_DepthBiasSlope;
	};
}
#endif // !VKPIPELINE_H
