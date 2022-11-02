#ifndef VKDESCRIPTORSET_H
#define VKDESCRIPTORSET_H
#include <Engine/Render/Vulkan/Vk.h>
#include <Engine/Render/Shader.h>
#include <Engine/Render/Renderer.h>
#include <Engine/Render/DescriptorSet.h>
#include <assert.h>
#include <vector>
#include <map>
namespace MeteorEngine
{

	struct Buffer
	{
		u8* Data;
		u32 Size;
		Buffer()
			: Data(NULL)
			, Size(0)
		{
		}

		Buffer(void* data, u32 size)
			: Data((u8*)data)
			, Size(size)
		{
		}

		static Buffer Copy(const void* data, u32 size)
		{
			Buffer buffer;
			buffer.Allocate(size);
			memcpy(buffer.Data, data, size);
			return buffer;
		}

		void Allocate(u32 size)
		{
			delete[] Data;
			Data = nullptr;

			if (size == 0)
				return;

			Data = new u8[size];
			Size = size;
		}

		void Release()
		{
			delete[] Data;
			Data = nullptr;
			Size = 0;
		}

		void InitialiseEmpty()
		{
			if (Data)
				memset(Data, 0, Size);
		}

		template <typename T>
		T& Read(u32 offset = 0)
		{
			return *(T*)((u8*)Data + offset);
		}

		u8* ReadBytes(u32 size, u32 offset)
		{
			assert(offset + size <= Size, "Index out of bounds");
			u8* buffer = new u8[size];
			memcpy(buffer, (u8*)Data + offset, size);
			return buffer;
		}

		void Write(void* data, u32 size, u32 offset = 0)
		{
			assert(offset + size <= Size, "Index out of bounds");
			memcpy((u8*)Data + offset, data, size);
		}
		operator bool() const
		{
			return Data;
		}

		u8& operator[](int index) { return ((u8*)Data)[index]; }

		u8 operator[](int index) const { return ((u8*)Data)[index]; }

		template <typename T>
		T* As() { return (T*)Data; }

		inline u32 GetSize() const { return Size; }
	};

	class METEOR_API VulkanDescriptorSet : public DescriptorSet
	{
	public:
		VulkanDescriptorSet();
		VulkanDescriptorSet(const DescriptorInfo&);
		virtual ~VulkanDescriptorSet();

		bool IsDynamic() const { return IsDynamic; }
		VkDescriptorSet GetDescriptorSet()
		{
			u32 currentFrame = RendererCommand::GetMainSwapChain()->GetCurrentBufferIndex();
			return m_DescriptorSet[currentFrame];
		}
		virtual void Update() override;
		virtual void SetUniform(const std::string& bufferName, const std::string& uniformName, void* data) override;
		//void SetBuffer(const std::string& name, UniformBuffer* buffer);
		virtual void SetUniform(const std::string& bufferName, const std::string& uniformName, void* data, u32 size) override;
		virtual void SetUniformBufferData(const std::string& bufferName, void* data) override;
		virtual void TransitionImages(CommandBuffer* commandBuffer) override;
	private:
		u32 m_DynamicOffset = 0;
		Shader* m_Shader = NULL;
		bool m_Dynamic = false;
		VkDescriptorBufferInfo	m_BufferInfoPool[32];
		VkDescriptorImageInfo	m_ImageInfoPool[32];
		VkWriteDescriptorSet	m_WriteDescriptorSetPool[32];
		u32 m_FramesInFlight = 0;
		struct UniformBufferInfo
		{
			std::vector<BufferMemberInfo> m_Members;
			Buffer LocalStorage;
			// Per frame in flight
			bool HasUpdated[10];
		};

		std::map<u32, VkDescriptorSet> m_DescriptorSet;
		DescriptorSetInfo m_Descriptors;
		std::map<u32, std::map<std::string, UniformBuffer* > > m_UniformBuffers;

		std::map<std::string, UniformBufferInfo> m_UniformBuffersData;
		bool m_DescriptorDirty[3];
		bool m_DescriptorUpdated[3];
	};
}
#endif // !VKDESCRIPTORSET_H
