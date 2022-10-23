#ifndef VULKANTEXTURE_H
#define VULKANTEXTURE_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Texture.h>
#include <Engine/Core/Config.h>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API VulkanTexture2D : public Texture2D
	{
	public:
		VulkanTexture2D();
		VulkanTexture2D(const std::string&, const TextureDesc&);
		VulkanTexture2D(const TextureDesc&, const Vector2u&);
		VulkanTexture2D(VkImage, VkImageView, VkFormat, const Vector2u&);
		~VulkanTexture2D();
		virtual void Resize(const Vector2u&) override;

		virtual void*		GetTexture() const override { return (void*)this; }

		virtual void* GetTextureHande() const override { return (void*)m_Image; }

		virtual void        Bind(u32 slot = 0) const override{}
		virtual void        UnBind(u32 slot = 0)    const override{}


		virtual RHIPixelFormat GetFormat() const override { return m_Format; }
		virtual Vector2u GetSize()	const override { return m_Size; }



		VkImage GetImage() const
		{
			return m_Image;
		};
		VkDeviceMemory GetDeviceMemory() const
		{
			return m_ImageMemory;
		}
		VkImageView GetImageView() const
		{
			return m_ImageView;
		}
		VkSampler GetSampler() const
		{
			return m_Sampler;
		}

		VkFormat GetVKFormat()
		{
			return m_VKFormat;
		}
		VkImageLayout GetImageLayout() const { return m_ImageLayout; }
		void TransitionImage(VkImageLayout newLayout, VkCommandBuffer commandBuffer = NULL);

		void UpdateDescriptor()
		{
			m_Descriptor.sampler = m_Sampler;
			m_Descriptor.imageView = m_ImageView;
			m_Descriptor.imageLayout = m_ImageLayout;
		}

		void BuildTexture();
		void Cleanup();
	private:
		u8* m_Pointer = NULL;
		bool					m_DeleteImage{ false };
		TextureDesc				m_Parameters;
		Vector2u				m_Size;
		RHIPixelFormat			m_Format = RHIPixelFormat::RGB8_UNORM;
		u32						m_MipLevels = 1;
		VkImage					m_Image{};
		VkImageLayout			m_ImageLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		VkDeviceMemory			m_ImageMemory{};
		VkImageView				m_ImageView{};
		VkSampler				m_Sampler{};
		VkDescriptorImageInfo	m_Descriptor{};
		VkFormat				m_VKFormat = VK_FORMAT_R8G8B8A8_UNORM;

	};
	class METEOR_API VulkanTextureDepth :  public TextureDepth
	{
	public:
		VulkanTextureDepth();
		VulkanTextureDepth( const Vector2u&);
		~VulkanTextureDepth();
		virtual RHIPixelFormat GetFormat() const override { return m_Format; }
		virtual Vector2u GetSize()	const override { return m_Size; }

		virtual void        Bind(u32 slot = 0) const override {}
		virtual void        UnBind(u32 slot = 0)    const override {}

		virtual void Resize(const Vector2u&) override;

		virtual void* GetTexture() const override { return (void*)this; }

		virtual void* GetTextureHande() const override { return (void*)m_Image; }

		VkImage GetImage() const { return m_Image; }
		VkDeviceMemory GetDeviceMemory() const { return m_ImageMemory; }
		VkImageView GetImageView() const { return m_ImageView; }
		VkSampler GetSampler() const { return m_Sampler; }
		VkFormat GetVKFormat() { return m_VKFormat; }

		void UpdateDescriptor()
		{
			m_Descriptor.sampler = m_Sampler;
			m_Descriptor.imageView = m_ImageView;
			m_Descriptor.imageLayout = m_ImageLayout;
		}
		VkImageLayout GetImageLayout() const { return m_ImageLayout; }
		void TransitionImage(VkImageLayout newLayout, VkCommandBuffer commandBuffer = NULL);
		void BuildTexture();
		void Cleanup();
	private:
		Vector2u				m_Size;
		RHIPixelFormat			m_Format;
		VkFormat				m_VKFormat;
		VkImageLayout			m_ImageLayout;
		VkImage					m_Image{};
		VkDeviceMemory			m_ImageMemory{};
		VkImageView				m_ImageView{};
		VkSampler				m_Sampler{};
		VkDescriptorImageInfo	m_Descriptor{};
	};
}
#endif // !VULKANTEXTURE_H
