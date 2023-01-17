#include <Engine/Render/Vulkan/VkShader.h>
#include <Engine/Render/Vulkan/VkPipeline.h>
#include <Engine/Render/Vulkan/VkCommandBuffer.h>
#include <Engine/Render/Vulkan/VkDevice.h>
#include <Engine/Render/Vulkan/VkUtilities.h>
#include <Engine/System/File.h>
#include <vector>
#include <fstream>
namespace MeteorEngine
{

	ShaderDataType  SPIRVTypeToMeteorDataType(const spirv_cross::SPIRType type)
	{
		switch (type.basetype)
		{
		case spirv_cross::SPIRType::Boolean:
			return ShaderDataType::Bool;
		case spirv_cross::SPIRType::Int:
			if (type.vecsize == 1)
				return ShaderDataType::Int;
			if (type.vecsize == 2)
				return ShaderDataType::Int2;
			if (type.vecsize == 3)
				return ShaderDataType::Int3;
			if (type.vecsize == 4)
				return ShaderDataType::Int4;

		case spirv_cross::SPIRType::UInt:
			return ShaderDataType::Int;


		case spirv_cross::SPIRType::Float:
			if (type.columns == 3)
				return ShaderDataType::Mat3;
			if (type.columns == 4)
				return ShaderDataType::Mat4;

			if (type.vecsize == 1)
				return ShaderDataType::Float;
			if (type.vecsize == 2)
				return ShaderDataType::Float2;
			if (type.vecsize == 3)
				return ShaderDataType::Float3;
			if (type.vecsize == 4)
				return ShaderDataType::Float4;
			break;
		case spirv_cross::SPIRType::Struct:
			return ShaderDataType::Struct;
		}
		LOGLN("Unknown spirv type!");
		return ShaderDataType::None;
	}
	VkFormat GetVulkanFormat(const spirv_cross::SPIRType& type)
	{
		using namespace spirv_cross;
		if (type.basetype == SPIRType::Struct || type.basetype == SPIRType::Sampler)
		{
			LOG("Tried to convert a structure or SPIR sampler into a VkFormat enum value!");
			return VK_FORMAT_UNDEFINED;
		}
		else if (type.basetype == SPIRType::Image || type.basetype == SPIRType::SampledImage)
		{
			switch (type.image.format)
			{
			case spv::ImageFormatR8:
				return VK_FORMAT_R8_UNORM;
			case spv::ImageFormatR8Snorm:
				return VK_FORMAT_R8_SNORM;
			case spv::ImageFormatR8ui:
				return VK_FORMAT_R8_UINT;
			case spv::ImageFormatR8i:
				return VK_FORMAT_R8_SINT;
			case spv::ImageFormatRg8:
				return VK_FORMAT_R8G8_UNORM;
			case spv::ImageFormatRg8Snorm:
				return VK_FORMAT_R8G8_SNORM;
			case spv::ImageFormatRg8ui:
				return VK_FORMAT_R8G8_UINT;
			case spv::ImageFormatRg8i:
				return VK_FORMAT_R8G8_SINT;
			case spv::ImageFormatRgba8i:
				return VK_FORMAT_R8G8B8A8_SINT;
			case spv::ImageFormatRgba8ui:
				return VK_FORMAT_R8G8B8A8_UINT;
			case spv::ImageFormatRgba8:
				return VK_FORMAT_R8G8B8A8_UNORM;
			case spv::ImageFormatRgba8Snorm:
				return VK_FORMAT_R8G8B8A8_SNORM;
			case spv::ImageFormatR32i:
				return VK_FORMAT_R32_SINT;
			case spv::ImageFormatR32ui:
				return VK_FORMAT_R32_UINT;
			case spv::ImageFormatRg32i:
				return VK_FORMAT_R32G32_SINT;
			case spv::ImageFormatRg32ui:
				return VK_FORMAT_R32G32_UINT;
			case spv::ImageFormatRgba32f:
				return VK_FORMAT_R32G32B32A32_SFLOAT;
			case spv::ImageFormatRgba16f:
				return VK_FORMAT_R16G16B16A16_SFLOAT;
			case spv::ImageFormatR32f:
				return VK_FORMAT_R32_SFLOAT;
			case spv::ImageFormatRg32f:
				return VK_FORMAT_R32G32_SFLOAT;
			case spv::ImageFormatR16f:
				return VK_FORMAT_R16_SFLOAT;
			case spv::ImageFormatRgba32i:
				return VK_FORMAT_R32G32B32A32_SINT;
			case spv::ImageFormatRgba32ui:
				return VK_FORMAT_R32G32B32A32_UINT;
			default:
				LOG("Failed to convert an image format to a VkFormat enum.");
				return VK_FORMAT_UNDEFINED;
			}
		}
		else if (type.vecsize == 1)
		{
			if (type.width == 8)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R8_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R8_UINT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 16)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R16_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R16_UINT;
				case SPIRType::Float:
					return VK_FORMAT_R16_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 32)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R32_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R32_UINT;
				case SPIRType::Float:
					return VK_FORMAT_R32_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 64)
			{
				switch (type.basetype)
				{
				case SPIRType::Int64:
					return VK_FORMAT_R64_SINT;
				case SPIRType::UInt64:
					return VK_FORMAT_R64_UINT;
				case SPIRType::Double:
					return VK_FORMAT_R64_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else
			{
				LOG("Invalid type width for conversion of SPIR-Type to VkFormat enum value!");
				return VK_FORMAT_UNDEFINED;
			}
		}
		else if (type.vecsize == 2)
		{
			if (type.width == 8)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R8G8_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R8G8_UINT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 16)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R16G16_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R16G16_UINT;
				case SPIRType::Float:
					return VK_FORMAT_R16G16_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 32)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R32G32_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R32G32_UINT;
				case SPIRType::Float:
					return VK_FORMAT_R32G32_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 64)
			{
				switch (type.basetype)
				{
				case SPIRType::Int64:
					return VK_FORMAT_R64G64_SINT;
				case SPIRType::UInt64:
					return VK_FORMAT_R64G64_UINT;
				case SPIRType::Double:
					return VK_FORMAT_R64G64_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else
			{
				LOG("Invalid type width for conversion of SPIR-Type to VkFormat enum value!");
				return VK_FORMAT_UNDEFINED;
			}
		}
		else if (type.vecsize == 3)
		{
			if (type.width == 8)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R8G8B8_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R8G8B8_UINT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 16)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R16G16B16_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R16G16B16_UINT;
				case SPIRType::Float:
					return VK_FORMAT_R16G16B16_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 32)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R32G32B32_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R32G32B32_UINT;
				case SPIRType::Float:
					return VK_FORMAT_R32G32B32_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 64)
			{
				switch (type.basetype)
				{
				case SPIRType::Int64:
					return VK_FORMAT_R64G64B64_SINT;
				case SPIRType::UInt64:
					return VK_FORMAT_R64G64B64_UINT;
				case SPIRType::Double:
					return VK_FORMAT_R64G64B64_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else
			{
				LOG("Invalid type width for conversion of SPIR-Type to VkFormat enum value!");
				return VK_FORMAT_UNDEFINED;
			}
		}
		else if (type.vecsize == 4)
		{
			if (type.width == 8)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R8G8B8A8_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R8G8B8A8_UINT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 16)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R16G16B16A16_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R16G16B16A16_UINT;
				case SPIRType::Float:
					return VK_FORMAT_R16G16B16A16_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 32)
			{
				switch (type.basetype)
				{
				case SPIRType::Int:
					return VK_FORMAT_R32G32B32A32_SINT;
				case SPIRType::UInt:
					return VK_FORMAT_R32G32B32A32_UINT;
				case SPIRType::Float:
					return VK_FORMAT_R32G32B32A32_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else if (type.width == 64)
			{
				switch (type.basetype)
				{
				case SPIRType::Int64:
					return VK_FORMAT_R64G64B64A64_SINT;
				case SPIRType::UInt64:
					return VK_FORMAT_R64G64B64A64_UINT;
				case SPIRType::Double:
					return VK_FORMAT_R64G64B64A64_SFLOAT;
				default:
					return VK_FORMAT_UNDEFINED;
				}
			}
			else
			{
				LOG("Invalid type width for conversion to a VkFormat enum");
				return VK_FORMAT_UNDEFINED;
			}
		}
		else
		{
			LOG("Vector size in vertex input attributes isn't explicitly supported for parsing from SPIRType->VkFormat");
			return VK_FORMAT_UNDEFINED;
		}
	}
	*/
	u32 GetStrideFromVulkanFormat(VkFormat format)
	{
		switch (format)
		{
		case VK_FORMAT_R8_SINT:
		case VK_FORMAT_R8_UINT:
		case VK_FORMAT_R32_SFLOAT:
			return 4;

		case VK_FORMAT_R32G32_UINT:
		case VK_FORMAT_R32G32_SINT:
		case VK_FORMAT_R32G32_SFLOAT:
			return 8;

		case VK_FORMAT_R32G32B32_UINT:
		case VK_FORMAT_R32G32B32_SINT:
		case VK_FORMAT_R32G32B32_SFLOAT:
			return 12;

		case VK_FORMAT_R32G32B32A32_SFLOAT:
		case VK_FORMAT_R32G32B32A32_SINT:
		case VK_FORMAT_R32G32B32A32_UINT:
			return 16;

		default:
			LOG("Unsupported Format {0}", format);
			return 0;
		}
		return 0;
	}
	/**static shaderc_shader_kind VulkanShaderStageToShaderC(VkShaderStageFlagBits stage)
	{
		switch (stage)
		{
			case VK_SHADER_STAGE_VERTEX_BIT:   return shaderc_glsl_vertex_shader;
			case VK_SHADER_STAGE_FRAGMENT_BIT: return shaderc_glsl_fragment_shader;
		}
		return (shaderc_shader_kind)0;
	}*/
	std::string ReadFile(const std::string& fileName)
	{
		File* file = File::Create(fileName, FileMode::OpenExisting, FileAccess::Read, FileShare::Read);
		u32 size = file->GetSize();
		std::string source;
		source.resize(size);
		file->Read(source.data(), source.size(), NULL);
		return source;
	}
	u8* ReadFileData(const std::string& fileName)
	{
		File* file = File::Create(fileName, FileMode::OpenExisting, FileAccess::Read, FileShare::Read);
		u32 size = file->GetSize();
		u8* source = new u8[size];
		file->Read(source, size, NULL);
		return source;
	}
	/**std::vector<u32> CompileGlslToSpirV(const std::string& fileName, VkShaderStageFlagBits stage)
	{
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2);
		options.SetOptimizationLevel(shaderc_optimization_level_performance);
		auto module = compiler.CompileGlslToSpv(ReadFile(fileName), VulkanShaderStageToShaderC(stage), fileName.c_str(), options);

		if (module.GetCompilationStatus() != shaderc_compilation_status_success)
			LOGLN(module.GetErrorMessage());
		
		return std::vector<u32>(module.cbegin(), module.cend());
	}*/
	VulkanShader::VulkanShader(const std::string& vert, const std::string& frag):
			m_StageCount(2), 
			m_PipelineLayout(0), 
			m_ShaderStages(NULL)
	{

		m_ShaderTypes = { ShaderType::VERTEX, ShaderType::FRAGMENT };
		m_ShaderStages = new VkPipelineShaderStageCreateInfo[m_StageCount];

		for (u32 i = 0; i < m_StageCount; i++)
			m_ShaderStages[i] = VkPipelineShaderStageCreateInfo();
		//std::vector<u32> pCodeVert(CompileGlslToSpirV(vert, VK_SHADER_STAGE_VERTEX_BIT));
		//std::vector<u32> pCodeFrag(CompileGlslToSpirV(frag, VK_SHADER_STAGE_FRAGMENT_BIT));
		std::string pCodeVert = ReadFile(vert);
		std::string pCodeFrag = ReadFile(frag);
		Load((u32*)pCodeVert.data(), pCodeVert.size(), ShaderType::VERTEX, 0);
		Load((u32*)pCodeFrag.data(), pCodeFrag.size(), ShaderType::FRAGMENT, 1);
		Compile();
	}
	VulkanShader::~VulkanShader()
	{

		for (u32 i = 0; i < m_StageCount; i++)
			vkDestroyShaderModule(VulkanDevice::GetInstance()->GetLogicalDevice(), m_ShaderStages[i].module, NULL);

		for (auto& descriptorLayout : m_DescriptorSetLayouts)
			vkDestroyDescriptorSetLayout(VulkanDevice::GetInstance()->GetLogicalDevice(), descriptorLayout, VK_NULL_HANDLE);

		if (m_PipelineLayout)
			vkDestroyPipelineLayout(VulkanDevice::GetInstance()->GetLogicalDevice(), m_PipelineLayout, VK_NULL_HANDLE);

		delete[] m_ShaderStages;

		for (auto& pc : m_PushConstants)
			delete[] pc.data;

		m_StageCount = 0;
	}

	void VulkanShader::BindPushConstants(CommandBuffer* commandBuffer, Pipeline* pipeline)
	{
		uint32_t index = 0;
		for (auto& pc : m_PushConstants)
		{
			vkCmdPushConstants(static_cast<VulkanCommandBuffer*>(commandBuffer)->GetCommandBuffer(), 
			static_cast<VulkanPipeline*>(pipeline)->GetPipelineLayout(), ShaderTypeToVK(pc.shaderStage), index, pc.size, pc.data);
		}
	}
	void VulkanShader::Load(const u32* source, u32 fileSize, ShaderType shaderType, u32 currStage)
	{


		std::vector<u32> spv(source, source + fileSize / sizeof(u32));

		spirv_cross::Compiler comp(std::move(spv));
		// The SPIR-V is now parsed, and we can perform reflection on it.
		spirv_cross::ShaderResources resources = comp.get_shader_resources();


		if (shaderType == ShaderType::VERTEX)
		{
			// Vertex Layout
			m_VertexInputStride = 0;

			for (const spirv_cross::Resource& resource : resources.stage_inputs)
			{
				const spirv_cross::SPIRType& InputType = comp.get_type(resource.type_id);

				VkVertexInputAttributeDescription Description = VkVertexInputAttributeDescription();
				Description.location = comp.get_decoration(resource.id, spv::DecorationLocation);
				Description.binding = comp.get_decoration(resource.id, spv::DecorationBinding);
				Description.offset = m_VertexInputStride;
				Description.format = GetVulkanFormat(InputType);
				m_VertexInputAttributeDescriptions.push_back(Description);

				m_VertexInputStride += GetStrideFromVulkanFormat(Description.format);
			}
		}
		// Descriptor Layout
		for (auto& u : resources.uniform_buffers)
		{
			u32 set = comp.get_decoration(u.id, spv::DecorationDescriptorSet);
			u32 binding = comp.get_decoration(u.id, spv::DecorationBinding);
			auto& type = comp.get_type(u.type_id);

			LOG("Found UBO {0} at set = {1}, binding = {2}", u.name.c_str(), set, binding);
			m_DescriptorLayoutInfo.push_back({ DescriptorType::UNIFORM_BUFFER, shaderType, binding, set, type.array.size() ? u32(type.array[0]) : 1 });

			auto & bufferType = comp.get_type(u.base_type_id);
			auto bufferSize = comp.get_declared_struct_size(bufferType);
			int memberCount = (int)bufferType.member_types.size();
			auto & descriptorInfo = m_DescriptorInfos[set];
			auto & descriptor = descriptorInfo.descriptors.emplace_back();
			descriptor.binding = binding;
			descriptor.size = (u32)bufferSize;
			descriptor.name = u.name;
			descriptor.offset = 0;
			descriptor.shaderType = shaderType;
			descriptor.type = DescriptorType::UNIFORM_BUFFER;
			descriptor.buffer = nullptr;

			for (int i = 0; i < memberCount; i++)
			{
				auto type = comp.get_type(bufferType.member_types[i]);
				const auto& memberName = comp.get_member_name(bufferType.self, i);
				auto size = comp.get_declared_struct_member_size(bufferType, i);
				auto offset = comp.type_struct_member_offset(bufferType, i);

				std::string uniformName = u.name + "." + memberName;

				auto& member = descriptor.m_Members.emplace_back();
				member.name = memberName;
				member.offset = offset;
				member.size = (u32)size;

				LOG("{0} - Size {1}, offset {2}", uniformName, size, offset);
			}
		}


		for (auto& u : resources.push_constant_buffers)
		{
			uint32_t set = comp.get_decoration(u.id, spv::DecorationDescriptorSet);
			uint32_t binding = comp.get_decoration(u.id, spv::DecorationBinding);

			uint32_t binding3 = comp.get_decoration(u.id, spv::DecorationOffset);

			auto& type = comp.get_type(u.type_id);

			auto ranges = comp.get_active_buffer_ranges(u.id);

			uint32_t size = 0;
			for (auto& range : ranges)
			{
				LOGLN("Accessing Member {0} offset {1}, size {2}", range.index, range.offset, range.range);
				size += uint32_t(range.range);
			}

			LOG("Found Push Constant {0} at set = {1}, binding = {2}", u.name.c_str(), set, binding, type.array.size() ? u32(type.array[0]) : 1);

			m_PushConstants.push_back({ size, shaderType });
			m_PushConstants.back().data = new uint8_t[size];

			auto & bufferType = comp.get_type(u.base_type_id);
			auto bufferSize = comp.get_declared_struct_size(bufferType);
			int memberCount = (int)bufferType.member_types.size();

			for (int i = 0; i < memberCount; i++)
			{
				auto type = comp.get_type(bufferType.member_types[i]);
				const auto& memberName = comp.get_member_name(bufferType.self, i);
				auto size = comp.get_declared_struct_member_size(bufferType, i);
				auto offset = comp.type_struct_member_offset(bufferType, i);
				std::string uniformName = u.name + "." + memberName;
				auto& member = m_PushConstants.back().m_Members.emplace_back();
				member.size = (uint32_t)size;
				member.offset = offset;
				member.type = SPIRVTypeToMeteorDataType(type);
				member.fullName = uniformName;
				member.name = memberName;
			}
		}

		m_ShaderStages[currStage].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		m_ShaderStages[currStage].stage = ShaderTypeToVK(shaderType);
		m_ShaderStages[currStage].pName = "main";
		m_ShaderStages[currStage].pNext = VK_NULL_HANDLE;

		VkShaderModuleCreateInfo shaderCreateInfo = VkShaderModuleCreateInfo();
		shaderCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		shaderCreateInfo.codeSize = fileSize;
		shaderCreateInfo.pCode = source;
		shaderCreateInfo.pNext = VK_NULL_HANDLE;
		if (vkCreateShaderModule(VulkanDevice::GetInstance()->GetLogicalDevice(), &shaderCreateInfo, nullptr, &m_ShaderStages[currStage].module) == VK_SUCCESS)
			m_Compiled = true;




	
	}
	void VulkanShader::Compile()
	{
		std::vector<std::vector<DescriptorLayoutInfo>> layouts;

		for (auto& descriptorLayout : GetDescriptorLayout())
		{
			while (layouts.size() < descriptorLayout.setID + 1)
				layouts.emplace_back();

			layouts[descriptorLayout.setID].push_back(descriptorLayout);
		}

		for (auto& l : layouts)
		{
			std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings;
			std::vector<VkDescriptorBindingFlags> layoutBindingFlags;
			setLayoutBindings.reserve(l.size());
			layoutBindingFlags.reserve(l.size());

			for (u32 i = 0; i < l.size(); i++)
			{
				auto& info = l[i];

				VkDescriptorSetLayoutBinding setLayoutBinding = VkDescriptorSetLayoutBinding();
				setLayoutBinding.descriptorType = DescriptorTypeToVK(info.type);
				setLayoutBinding.stageFlags = ShaderTypeToVK(info.stage);
				setLayoutBinding.binding = info.binding;
				setLayoutBinding.descriptorCount = info.count;

				bool isArray = info.count > 1;
				layoutBindingFlags.push_back(isArray ? VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT : 0);
				setLayoutBindings.push_back(setLayoutBinding);
			}

			VkDescriptorSetLayoutBindingFlagsCreateInfo flagsInfo = {};
			flagsInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
			flagsInfo.pNext = NULL;
			flagsInfo.bindingCount = static_cast<u32>(layoutBindingFlags.size());
			flagsInfo.pBindingFlags = layoutBindingFlags.data();

			// Pipeline layout
			VkDescriptorSetLayoutCreateInfo setLayoutCreateInfo = {};
			setLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			setLayoutCreateInfo.bindingCount = static_cast<u32>(setLayoutBindings.size());
			setLayoutCreateInfo.pBindings = setLayoutBindings.data();
			setLayoutCreateInfo.pNext = &flagsInfo;

			VkDescriptorSetLayout layout;
			vkCreateDescriptorSetLayout(VulkanDevice::GetInstance()->GetLogicalDevice(), &setLayoutCreateInfo, VK_NULL_HANDLE, &layout);

			m_DescriptorSetLayouts.push_back(layout);
		}

		const auto& pushConsts = GetPushConstants();
		std::vector<VkPushConstantRange> pushConstantRanges;

		for (auto& pushConst : pushConsts)
		{
			VkPushConstantRange pushConstantRange = VkPushConstantRange();

			pushConstantRange.stageFlags = ShaderTypeToVK(pushConst.shaderStage);
			pushConstantRange.offset = pushConst.offset;
			pushConstantRange.size = pushConst.size;
			pushConstantRanges.push_back(pushConstantRange);
		}

		auto& descriptorSetLayouts = GetDescriptorLayouts();

		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = VkPipelineLayoutCreateInfo();
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutCreateInfo.setLayoutCount = static_cast<u32>(descriptorSetLayouts.size());
		pipelineLayoutCreateInfo.pSetLayouts = descriptorSetLayouts.data();
		pipelineLayoutCreateInfo.pushConstantRangeCount = u32(pushConstantRanges.size());
		pipelineLayoutCreateInfo.pPushConstantRanges = pushConstantRanges.data();

		vkCreatePipelineLayout(VulkanDevice::GetInstance()->GetLogicalDevice(), &pipelineLayoutCreateInfo, VK_NULL_HANDLE, &m_PipelineLayout);

	}
}