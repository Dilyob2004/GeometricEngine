#ifndef RHIVIEWPORT_H
#define RHIVIEWPORT_H
#include <Engine/Core/Config.h>
namespace MeteorEngine
{
	class RHIViewport { public: virtual ~RHIViewport(){} };
	class RHIPixelShader { public: virtual ~RHIPixelShader() {} };
	class RHIVertexShader { public: virtual ~RHIVertexShader() {} };
	enum class ShaderElementType
	{
		Int,	Int2,	Int3,	Int4, 
		Mat,	Mat2,	Mat3,	Mat4,
		Float,	Float2,	Float3,	Float4,
		None
	};
	struct BufferElement
	{
		BufferElement()
			: BufferName("")
			, BufferType(ShaderElementType::None)
		{
		}
		BufferElement(const std::string& Name, ShaderElementType Type)
			: BufferName(Name)
			, BufferType(Type)
		{
		}
		std::string			BufferName;
		ShaderElementType	BufferType;
	};
	class VertexLayoutGroup
	{
	public:
		VertexLayoutGroup() = default;
		VertexLayoutGroup(std::initializer_list<BufferElement> Elements):
			Groups(Elements)
		{
		}
		u32 GetCountGroups() const { return Groups.size(); }
		const std::vector<BufferElement>& GetVertexGroup() const { return Groups; }
		std::vector<BufferElement>::iterator begin() { return Groups.begin(); }
		std::vector<BufferElement>::iterator end() { return Groups.end(); }		
		std::vector<BufferElement>::const_iterator begin() const { return Groups.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return Groups.end(); }

	private:
		std::vector<BufferElement> Groups;
	};
	class RHIVertexLayout
	{
	public:
		virtual ~RHIVertexLayout() {}
	};
	class RHIVertexBuffer
	{
	public:
		virtual ~RHIVertexBuffer() {}
		virtual void* GetPointer() const = 0;
		virtual u32 GetSize() const = 0;
	};
	class RHIIndexBuffer
	{
	public:
		virtual ~RHIIndexBuffer() {}
		virtual u32* GetPointer() const = 0;
		virtual u32 GetSize() const = 0;
	};
	class METEOR_API RHIShaderCompiler
	{
	public:
		virtual ~RHIShaderCompiler() {}
		static RHIShaderCompiler* StaticCreate();
		virtual bool Compile(const WCHAR* Path,
			const CHAR* EntryPoint,
			const CHAR* Target) = 0;
		virtual const std::vector<u32>& GetResultCode() const = 0;
	};
}
#endif // !RHIVIEWPORT_H
