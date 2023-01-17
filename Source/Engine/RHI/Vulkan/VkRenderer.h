#ifndef VKRENDERER_H
#define VKRENDERER_H

#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/SwapChain.h>
#include <Engine/Render/Renderer.h>
#include <Engine/Render/Pipeline.h>
#include <Engine/Render/DescriptorSet.h>
namespace MeteorEngine
{

	class METEOR_API VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer();
		~VulkanRenderer();
		virtual void Init(RenderContext*,  const Vector2u& size, bool vsync) override;
		virtual void Begin() override;
		virtual void Present() override;
		virtual void Resize(const Vector2u& size) override;
		virtual void ClearSwapChainImages() const override;
		static VkDescriptorPool GetDescriptorPool() { return s_DescriptorPool; }
		virtual void DrawIndexed(CommandBuffer* commandBuffer, DrawType type, u32 count, u32 start) const override;
		virtual void ClearRenderTarget(Texture* texture, CommandBuffer* commandBuffer, const Vector4f& clearColour)override;
		virtual SwapChain* GetMainSwapChain() const override { return m_SwapChain; }
		virtual void BindDescriptorSets(Pipeline* pipeline, CommandBuffer* commandBuffer, u32 dynamicOffset, DescriptorSet** descriptorSets, u32 descriptorCount) override;

	private:
		SwapChain* m_SwapChain;
		u32 m_DescriptorCapacity = 0;
		static VkDescriptorPool s_DescriptorPool;
		VkDescriptorSet m_DescriptorSetPool[16]{};
	};
}

#endif // !VKRENDERER_H
