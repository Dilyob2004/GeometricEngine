#ifndef RHIVIEWPORT_H
#define RHIVIEWPORT_H
#include <Engine/Core/Config.h>
namespace GeometricEngine
{
	enum class RHIPixelFormat : U32
	{
		NONE = 0,

		R8_UNORM,
		RG8_UNORM,
		RGB8_UNORM,
		RGBA8_UNORM,

		R8_U32,

		RG11B10_F32,
		RGB10A2_UNORM,

		R32_S32,
		RG32_S32,
		RGB32_S32,
		RGBA32_S32,

		R32_U32,
		RG32_U32,
		RGB32_U32,
		RGBA32_U32,

		R16_F32,
		RG16_F32,
		RGB16_F32,
		RGBA16_F32,

		R32_F32,
		RG32_F32,
		RGB32_F32,
		RGBA32_F32,

		DEPTH16_UNORM,
		DEPTH32_F32,

		DEPTH16_UNORM_STENCIL8_U32,
		DEPTH24_UNORM_STENCIL8_U32,
		DEPTH32_F32_STENCIL8_U32
	};

	enum class BlendMode
	{
		None = 0,
		OneZero,
		ZeroSrcColor,
		SrcAlphaOneMinusSrcAlpha,
	};
	enum class ShaderElementType
	{
		Int, Int2, Int3, Int4,
		Mat, Mat2, Mat3, Mat4,
		Float, Float2, Float3, Float4,
		None
	};
	enum class DrawType
	{
		POINT,
		TRIANGLES,
		LINES
	};

	static U32 GetShaderStrideType(ShaderElementType type)
	{
		switch (type)
		{
		case ShaderElementType::Float:
		case ShaderElementType::Int:
			return 1;
		case ShaderElementType::Float2:
		case ShaderElementType::Int2:
			return 2;
		case ShaderElementType::Float3:
		case ShaderElementType::Int3:
			return 3;
		case ShaderElementType::Float4:
		case ShaderElementType::Int4:
			return 4;


		default:
			return 0;
		}
	}
	static U32 GetSizeOfShaderType(ShaderElementType type)
	{

		switch (type)
		{
			case ShaderElementType::Float:
			case ShaderElementType::Float2:
			case ShaderElementType::Float3:
			case ShaderElementType::Float4:
				return 4;


		default:
			return 0;
		}
	}
	class GEOMETRIC_API RHIViewport { public: virtual ~RHIViewport(){} };
	class GEOMETRIC_API RHIPixelShader { public: virtual ~RHIPixelShader() {} };
	class GEOMETRIC_API RHIVertexShader { public: virtual ~RHIVertexShader() {} };
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
		U32 GetStrideLayout() const
		{
			U32 Stride = 0;
			for (auto& Element : Groups)
				Stride += GetShaderStrideType(Element.BufferType) * GetSizeOfShaderType(Element.BufferType);
			
			return Stride;
		}
		U32 GetCountGroups() const { return Groups.size(); }
		const std::vector<BufferElement>& GetVertexGroup() const { return Groups; }
		std::vector<BufferElement>::iterator begin() { return Groups.begin(); }
		std::vector<BufferElement>::iterator end() { return Groups.end(); }		
		std::vector<BufferElement>::const_iterator begin() const { return Groups.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return Groups.end(); }

	private:
		std::vector<BufferElement> Groups;
	};
	class GEOMETRIC_API RHIVertexLayout
	{
	public:
		virtual ~RHIVertexLayout() {}

		virtual U32 GetStrideLayout() = 0;
	};
	class GEOMETRIC_API RHIVertexBuffer
	{
	public:
		virtual ~RHIVertexBuffer() {}
		virtual void* GetPointer() const = 0;
		virtual U32 GetSize() const = 0;
	};
	class GEOMETRIC_API RHIIndexBuffer
	{
	public:
		virtual ~RHIIndexBuffer() {}
		virtual U32* GetPointer() const = 0;
		virtual U32 GetSize() const = 0;
	};
	class GEOMETRIC_API RHIConstantBuffer
	{
	public:
		virtual ~RHIConstantBuffer() {}
		virtual void* GetPointer() const = 0;
		virtual U32 GetSize() const = 0;
	};
	class GEOMETRIC_API RHIShaderCompiler
	{
	public:
		virtual ~RHIShaderCompiler() {}
		static RHIShaderCompiler* StaticCreate();
		virtual bool Compile(const WCHAR* Path,
			const CHAR* EntryPoint,
			const CHAR* Target) = 0;
		virtual const std::vector<U32>& GetResultCode() const = 0;
	};
}
#endif // !RHIVIEWPORT_H
