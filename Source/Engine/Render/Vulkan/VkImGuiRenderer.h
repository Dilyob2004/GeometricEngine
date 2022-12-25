#ifndef VKIMGUIRENDERER_H
#define VKIMGUIRENDERER_H

#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/ImGuiRenderer.h>
#include <ImGui/imgui_impl_vulkan.h>
namespace MeteorEngine
{
	class VulkanFrameBuffer;
	class VulkanRenderPass;
	class VulkanTexture2D;
	class METEOR_API VulkanImGuiRenderer : public ImGuiRenderer
	{
	public:
		VulkanImGuiRenderer(const Vector2u& size, bool);
		virtual ~VulkanImGuiRenderer();

		void Init() ;
		virtual void Render() override;
		virtual void OnResize(const Vector2u& size) override;
		virtual void Clear() override;
		virtual void BuildFontTexture()override;
		void FrameRender(ImGui_ImplVulkanH_Window* wd);
		void SetupVulkanWindowData(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, const Vector2u&);
		
	private:
		Vector2u			m_Size;
		VulkanFrameBuffer*	m_Framebuffers[3];
		VulkanRenderPass*	m_Renderpass;
		VulkanTexture2D*	m_FontTexture;
		bool				m_ClearScreen;
	};
}
#endif // !VKIMGUIRENDERER_H
