#ifndef VULKANTEXTURE_H
#define VULKANTEXTURE_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Texture.h>
#include <Engine/Core/Config.h>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API VulkanTexture : public Texture
	{
	public:
		VulkanTexture();
		VulkanTexture(const std::string&){}
		VulkanTexture(const std::string&, const TextureDesc&){}
		VulkanTexture(const TextureDesc&, u32, u32){}
		VulkanTexture(const TextureDesc&, u32, u32, u8*){}
		~VulkanTexture();

		virtual u32			GetTexture() const override { return 0; }
		virtual void        Bind(u32 slot = 0) const override{}
		virtual void        UnBind(u32 slot = 0)    const override{}


		virtual RHITextureFormat GetFormat() const override { return m_Format; }
		virtual Vector2u GetSize()	const override { return m_Size; }

	private:
		Vector2u m_Size;
		RHITextureFormat m_Format;
	};
}
#endif // !VULKANTEXTURE_H
