#ifndef STRUCTS_H
#define STRUCTS_H

#include <Engine/core/Config.h>
#include <vector>
namespace MeteorEngine
{
	class Texture;
	class Shader;
	class UniformBuffer;
	
	struct BufferMemberInfo
	{
		u32 size;
		u32 offset;
		ShaderDataType type;
		std::string name;
		std::string fullName;
	};
	struct DescriptorLayoutInfo
	{
		DescriptorType type;
		ShaderType stage;
		u32 binding = 0;
		u32 setID = 0;
		u32 count = 1;
	};
	struct Descriptor
	{
		Texture** textures;
		Texture* texture;
		UniformBuffer* buffer;

		u32 offset;
		u32 size;
		u32 binding;
		u32 textureCount = 1;
		u32 mipLevel = 0;
		std::string name;

		TextureType textureType;
		DescriptorType type = DescriptorType::IMAGE_SAMPLER;
		ShaderType shaderType;

		std::vector<BufferMemberInfo> m_Members;
	};
	struct DescriptorSetInfo
	{
		std::vector<Descriptor> descriptors;
	};
	struct DescriptorInfo
	{
		u32 layoutIndex;
		Shader* shader;
		u32 count = 1;
	};
	struct PushConstant
	{
		uint32_t size;
		ShaderType shaderStage;
		uint8_t* data;
		uint32_t offset = 0;
		std::string name;

		std::vector<BufferMemberInfo> m_Members;

		void SetValue(const std::string& name, void* value)
		{
			for (auto& member : m_Members)
			{
				if (member.name == name)
				{
					memcpy(&data[member.offset], value, member.size);
					break;
				}
			}
		}

		void SetData(void* value)
		{
			memcpy(data, value, size);
		}
	};
}

#endif