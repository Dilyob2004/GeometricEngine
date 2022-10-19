#include <Engine/Render/Texture.h>
#include <Engine/Render/Vulkan/VkTexture.h>
namespace MeteorEngine
{
	Texture2D* Texture2D::Create(const TextureDesc& parameters, const Vector2u& size)
	{
		return new VulkanTexture2D(parameters, size);
	}
}
