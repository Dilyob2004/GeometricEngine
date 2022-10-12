#include <Engine/Render/Texture.h>
#include <Engine/Render/Vulkan/VkTexture.h>
namespace MeteorEngine
{
	Texture* Texture::Create(const std::string& path)
    {
		return new VulkanTexture(path);
    }
	Texture* Texture::Create(const TextureDesc& desc, u32 width, u32 height)
    {
		return new VulkanTexture(desc, width, height);
    }
	Texture* Texture::Create(const std::string& path, const TextureDesc& desc)
	{
		return new VulkanTexture(path, desc);
	}
	Texture* Texture::Create(const TextureDesc& desc, u32 width, u32 height, u8* data)
	{
		return new VulkanTexture(desc, width, height, data);
	}
}
