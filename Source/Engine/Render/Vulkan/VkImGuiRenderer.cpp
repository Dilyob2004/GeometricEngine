#include <Engine/Render/Vulkan/VkImGuiRenderer.h>

#include <Engine/Render/Renderer.h>
#include <Engine/Render/Vulkan/VkContext.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkTexture.h>
#include <Engine/Render/Vulkan/VkFrameBuffer.h>
#include <Engine/Render/Vulkan/VkSwapChain.h>
#include <Engine/Render/Vulkan/VkRenderPass.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_impl_vulkan.h>
#include <ImGui/imgui_internal.h>
namespace MeteorEngine
{

	static ImGui_ImplVulkanH_Window g_WindowData;
	static VkAllocationCallbacks* g_Allocator = nullptr;
	static VkDescriptorPool g_DescriptorPool = VK_NULL_HANDLE;
	VulkanImGuiRenderer::VulkanImGuiRenderer(const Vector2u& size, bool clear):
		m_Framebuffers {},
		m_Renderpass(NULL),
		m_FontTexture(),
		m_Size(size),
		m_ClearScreen(clear)
	{
		Init();
	}
	VulkanImGuiRenderer::~VulkanImGuiRenderer()
	{

		for (int i = 0; i < RendererCommand::GetMainSwapChain()->GetSwapChainBufferCount(); i++)
		{
			delete m_Framebuffers[i];
		}

		delete m_Renderpass;
		delete m_FontTexture;

	}

	void VulkanImGuiRenderer::Init()
	{
		int w, h;
		w = (int)m_Size.x;
		h = (int)m_Size.y;
		ImGui_ImplVulkanH_Window* wd = &g_WindowData;
		SetupVulkanWindowData(wd, VulkanContext::GetInstance()->GetSurface(), { (u32)w, (u32)h });

		// Setup Vulkan binding
		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = VulkanContext::GetInstance()->GetVulkanInstance();
		init_info.PhysicalDevice = VulkanDevice::GetInstance()->GetPhysicalDevice();
		init_info.Device = VulkanDevice::GetInstance()->GetLogicalDevice();
		init_info.QueueFamily = VulkanDevice::GetInstance()->GetQueueFamilyIndex();
		init_info.Queue = VulkanDevice::GetInstance()->GetQueue();
		init_info.PipelineCache = VulkanDevice::GetInstance()->GetPipelineCache();
		init_info.DescriptorPool = g_DescriptorPool;
		init_info.Allocator = g_Allocator;
		init_info.CheckVkResultFn = NULL;
		init_info.MinImageCount = 2;
		init_info.ImageCount = (u32)RendererCommand::GetMainSwapChain()->GetSwapChainBufferCount();
		ImGui_ImplVulkan_Init(&init_info, wd->RenderPass);
		BuildFontTexture();
	}
	void VulkanImGuiRenderer::Render()
	{
		ImGui::Render();
		FrameRender(&g_WindowData);
	}
	void VulkanImGuiRenderer::OnResize(const Vector2u& size)
	{

		auto* wd = &g_WindowData;
		auto swapChain = static_cast<VulkanSwapChain*>(RendererCommand::GetMainSwapChain());
		wd->Swapchain = swapChain->GetSwapChain();
		for (uint32_t i = 0; i < wd->ImageCount; i++)
		{
			auto scBuffer = (VulkanTexture2D*)swapChain->GetImage(i);
			wd->Frames[i].Backbuffer = scBuffer->GetImage();
			wd->Frames[i].BackbufferView = scBuffer->GetImageView();
		}

		wd->Width = size.x;
		wd->Height = size.y;

		for (uint32_t i = 0; i < wd->ImageCount; i++)
		{
			delete m_Framebuffers[i];
		}
		// Create Framebuffer
		TextureType attachmentTypes[1] = { TextureType::COLOR };

		Texture* attachments[1];
		FrameBufferDesc frameBufferDesc{};
		frameBufferDesc.Size.x = wd->Width;
		frameBufferDesc.Size.y = wd->Height;
		frameBufferDesc.AttachmentCount = 1;
		frameBufferDesc.RenderPass = m_Renderpass;
		frameBufferDesc.AttachmentTypes = attachmentTypes;
		frameBufferDesc.ScreenFBO = true;

		for (uint32_t i = 0; i < RendererCommand::GetMainSwapChain()->GetSwapChainBufferCount(); i++)
		{
			attachments[0] = RendererCommand::GetMainSwapChain()->GetImage(i);
			frameBufferDesc.Attachments = attachments;

			m_Framebuffers[i] = new VulkanFrameBuffer(frameBufferDesc);
			wd->Frames[i].Framebuffer = m_Framebuffers[i]->GetFrameBuffer();
		}
	}
	void VulkanImGuiRenderer::Clear()
	{

	}

	void VulkanImGuiRenderer::FrameRender(ImGui_ImplVulkanH_Window* wd)
	{

		wd->FrameIndex = RendererCommand::GetMainSwapChain()->GetCurrentImageIndex();
		/**auto& descriptorImageMap = ImGui_ImplVulkan_GetDescriptorImageMap();

		{
			auto draw_data = ImGui::GetDrawData();
			for (int n = 0; n < draw_data->CmdListsCount; n++)
			{
				const ImDrawList* cmd_list = draw_data->CmdLists[n];
				for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
				{
					const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];

					if ((Texture*)pcmd->TextureId)
					{
						if (((Texture*)pcmd->TextureId)->GetType() == TextureType::COLOR)
						{
							auto texture = (VulkanTexture2D*)pcmd->TextureId;
							texture->TransitionImage(VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, ((VulkanCommandBuffer*)RendererCommand::GetMainSwapChain()->GetCurrentCommandBuffer())->GetCommandBuffer());
							descriptorImageMap[pcmd->TextureId] = texture->GetDescriptor();
						}
						else if (((Texture*)pcmd->TextureId)->GetType() == TextureType::DEPTH)
						{
							auto texture = (VulkanTextureDepth*)pcmd->TextureId;
							texture->TransitionImage(VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL, ((VulkanCommandBuffer*)RendererCommand::GetMainSwapChain()->GetCurrentCommandBuffer())->GetCommandBuffer());
							descriptorImageMap[pcmd->TextureId] = texture->GetDescriptor();
						}
					}
				}
			}
		}

		ImGui_ImplVulkan_CreateDescriptorSets(ImGui::GetDrawData(), RendererCommand::GetMainSwapChain()->GetCurrentBufferIndex());*/
		
		float clearColour[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
		auto cmd = RendererCommand::GetMainSwapChain()->GetCurrentCommandBuffer();
		m_Renderpass->BeginRenderpass(cmd, clearColour, m_Framebuffers[wd->FrameIndex], SubPassContents::INLINE, { (u32)wd->Width, (u32)wd->Height });

		{
			// Record Imgui Draw Data and draw funcs into command buffer
			ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), ((VulkanCommandBuffer*)cmd)->GetCommandBuffer(), VK_NULL_HANDLE, RendererCommand::GetMainSwapChain()->GetCurrentBufferIndex());
		}
		m_Renderpass->EndRenderpass(cmd);
	}
	void VulkanImGuiRenderer::SetupVulkanWindowData(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, const Vector2u& size)
	{

		// Create Descriptor Pool
		{
			VkDescriptorPoolSize pool_sizes[] = {
				{ VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
				{ VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
				{ VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
				{ VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
				{ VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
				{ VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
			};
			VkDescriptorPoolCreateInfo pool_info = {};
			pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
			pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
			pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
			pool_info.pPoolSizes = pool_sizes;
			VkResult err = vkCreateDescriptorPool(VulkanDevice::GetInstance()->GetLogicalDevice(), &pool_info, g_Allocator, &g_DescriptorPool);
		}

		auto swapChain = static_cast<VulkanSwapChain*>(RendererCommand::GetMainSwapChain());
		wd->Surface = surface;
		wd->ClearEnable = m_ClearScreen;

		wd->Swapchain = swapChain->GetSwapChain();
		wd->Width = size.x;
		wd->Height = size.y;

		wd->ImageCount = static_cast<uint32_t>(swapChain->GetSwapChainBufferCount());

		TextureType textureTypes[1] = { TextureType::COLOR };

		Texture* textures[1] = { swapChain->GetImage(0) };

		RenderPassDesc renderPassDesc;
		renderPassDesc.AttachmentCount = 1;
		renderPassDesc.AttachmentTypes = textureTypes;
		renderPassDesc.Clear = m_ClearScreen;
		renderPassDesc.Attachments = textures;

		m_Renderpass = new VulkanRenderPass(renderPassDesc);
		wd->RenderPass = m_Renderpass->GetRenderPass();

		wd->Frames = (ImGui_ImplVulkanH_Frame*)IM_ALLOC(sizeof(ImGui_ImplVulkanH_Frame) * wd->ImageCount);
		// wd->FrameSemaphores = (ImGui_ImplVulkanH_FrameSemaphores*)IM_ALLOC(sizeof(ImGui_ImplVulkanH_FrameSemaphores) * wd->ImageCount);
		memset(wd->Frames, 0, sizeof(wd->Frames[0]) * wd->ImageCount);
		// memset(wd->FrameSemaphores, 0, sizeof(wd->FrameSemaphores[0]) * wd->ImageCount);

		// Create The Image Views
		{
			for (uint32_t i = 0; i < wd->ImageCount; i++)
			{
				auto scBuffer = (VulkanTexture2D*)swapChain->GetImage(i);
				wd->Frames[i].Backbuffer = scBuffer->GetImage();
				wd->Frames[i].BackbufferView = scBuffer->GetImageView();
			}
		}

		TextureType attachmentTypes =  TextureType::COLOR;

		Texture* attachments[1];
		FrameBufferDesc frameBufferDesc{};
		frameBufferDesc.Size.x = wd->Width;
		frameBufferDesc.Size.y = wd->Height;
		frameBufferDesc.AttachmentCount = 1;
		frameBufferDesc.RenderPass = m_Renderpass;
		frameBufferDesc.AttachmentTypes = &attachmentTypes;
		frameBufferDesc.ScreenFBO = true;

		for (uint32_t i = 0; i < RendererCommand::GetMainSwapChain()->GetSwapChainBufferCount(); i++)
		{
			attachments[0] = RendererCommand::GetMainSwapChain()->GetImage(i);
			frameBufferDesc.Attachments = attachments;

			m_Framebuffers[i] = new VulkanFrameBuffer(frameBufferDesc);
			wd->Frames[i].Framebuffer = m_Framebuffers[i]->GetFrameBuffer();
		}
	}
	void VulkanImGuiRenderer::BuildFontTexture()
	{
		// Upload Fonts
		{
			ImGuiIO& io = ImGui::GetIO();

			unsigned char* pixels;
			int width, height;
			io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
			TextureDesc desc;
			desc.MinFilter = TextureFilter::NEAREST;
			desc.MagFilter = TextureFilter::NEAREST;
			desc.WrapMode = TextureWrap::REPEAT;
			m_FontTexture = new VulkanTexture2D(desc, {(u32)width, (u32)height}, pixels);
			io.Fonts->TexID = (ImTextureID)m_FontTexture->GetTexture();
		}
	}

}