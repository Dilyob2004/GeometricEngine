#ifndef VKRENDERER_H
#define VKRENDERER_H

#include <Engine/Render/Vulkan/VkSwapChain.h>
#include <Engine/Render/Renderer.h>

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

		VulkanSwapChain* GetMainSwapChain() const { return m_SwapChain; }
	private:
		VulkanSwapChain* m_SwapChain;
		u32 m_DescriptorCapacity = 0;

		static VkDescriptorPool s_DescriptorPool;
		VkDescriptorSet m_DescriptorSetPool[16] = {};
	};
}

#endif // !VKRENDERER_H
