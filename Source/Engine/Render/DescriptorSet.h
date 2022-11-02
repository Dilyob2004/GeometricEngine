#ifndef DESCRIPTORSET_H
#define DESCRIPTORSET_H
#include <Engine/Render/CommandBuffer.h>
#include <Engine/Render/Structs.h>
namespace MeteorEngine
{
	class METEOR_API DescriptorSet
	{
	public:
		
		virtual ~DescriptorSet() {}
		static DescriptorSet* Create(const DescriptorInfo&);
		virtual void Update() = 0;
		virtual void SetUniform(const std::string& bufferName, const std::string& uniformName, void* data) = 0;
		//void SetBuffer(const std::string& name, UniformBuffer* buffer);
		virtual void SetUniform(const std::string& bufferName, const std::string& uniformName, void* data, u32 size) = 0;
		virtual void SetUniformBufferData(const std::string& bufferName, void* data) = 0;
		virtual void TransitionImages(CommandBuffer* commandBuffer) = 0;
	};
}
#endif // !DESCRIPTORSET_H
