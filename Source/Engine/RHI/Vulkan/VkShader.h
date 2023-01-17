#ifndef VKSHADER_H
#define VKSHADER_H

#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Structs.h>
#include <Engine/Render/Shader.h>
#include <map>
#include <unordered_map>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API VulkanShader : public Shader
	{
	public:
		VulkanShader(const std::string& vert, const std::string& frag);
		~VulkanShader();



		void BindPushConstants(CommandBuffer* commandBuffer, Pipeline* pipeline) override;
		DescriptorSetInfo GetDescriptorInfo(u32 index) override
		{
			if (m_DescriptorInfos.find(index) != m_DescriptorInfos.end())
			{
				return m_DescriptorInfos[index];
			}
			//LOG("DescriptorDesc not found. Index = {0}", index);
			return DescriptorSetInfo();
		}
		const std::vector<ShaderType> GetShaderTypes() const override { return std::vector<ShaderType>(); }
		bool IsCompiled() const override { return m_Compiled; }
		std::vector<PushConstant>& GetPushConstants()  override { return m_PushConstants; }

		const std::vector<DescriptorLayoutInfo>& GetDescriptorLayout() const { return m_DescriptorLayoutInfo; }
		
		VkDescriptorSetLayout* GetDescriptorLayout(i32 id) 
		{
			if (id < m_DescriptorSetLayouts.size())
			{
				return &m_DescriptorSetLayouts[id];
			}
			else
				return NULL;

		}
		VkPipelineLayout GetPipelineLayout() const { return m_PipelineLayout; }		
		
		const std::vector<VkDescriptorSetLayout>& GetDescriptorLayouts() const { return m_DescriptorSetLayouts; }

		VkPipelineShaderStageCreateInfo* GetShaderStages() const { return m_ShaderStages; }
		u32 GetStageCount() const { return m_StageCount; }
		const std::vector<VkVertexInputAttributeDescription>& GetVertexInputAttributeDescription() const { return m_VertexInputAttributeDescriptions; }
		const u32 GetVertexInputStride() const { return m_VertexInputStride; }
	private:
		void Load(const u32*, u32, ShaderType, u32);
		void Compile();
	private:

		std::vector<PushConstant> m_PushConstants;
		std::unordered_map<u32, DescriptorSetInfo> m_DescriptorInfos;
		std::vector<DescriptorLayoutInfo> m_DescriptorLayoutInfo;
		VkPipelineShaderStageCreateInfo* m_ShaderStages;
		uint32_t m_StageCount = 0;


		std::vector<VkVertexInputAttributeDescription> m_VertexInputAttributeDescriptions;
		uint32_t m_VertexInputStride = 0;

		VkPipelineLayout m_PipelineLayout;
		std::vector<ShaderType> m_ShaderTypes;
		bool m_Compiled = false;
		std::vector<VkDescriptorSetLayout> m_DescriptorSetLayouts;
	};
}
#endif // !VKSHADER_H
