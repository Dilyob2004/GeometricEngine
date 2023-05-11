#ifndef DX11BUFFER_H
#define DX11BUFFER_H
#include <Engine/RHI/RHIResources.h>
#include <d3d11.h>
namespace GeometricEngine
{

	struct VertexBufferView
	{
		VertexBufferView()
			: Data(NULL)
			, Size(0)
			, Stride(0)
			, Offset(0)
		{
		}
		const void* Data;
		U32 Size;
		U32 Stride;
		U32 Offset;
	};
	class DX11VertexBuffer : public RHIVertexBuffer
	{
	public:
		DX11VertexBuffer();

		DX11VertexBuffer(ID3D11Buffer* , const VertexBufferView& );

		virtual ~DX11VertexBuffer();

		VertexBufferView GetBufferView() const { return BufferView; }

		ID3D11Buffer* GetVertexBuffer() const { return DXVertexBuffer; }
		ID3D11Buffer** GetInitVertexBuffer() { return &DXVertexBuffer; }

	private:
		VertexBufferView BufferView;

		ID3D11Buffer* DXVertexBuffer;

	};

	class DX11IndexBuffer : public RHIIndexBuffer
	{
	public:
		DX11IndexBuffer();

		DX11IndexBuffer(ID3D11Buffer*, U32 Size, const U32*);

		virtual ~DX11IndexBuffer();

		const U32* GetPointer() const { return Buffer; }

		U32 GetSize() const { return Size; }

		ID3D11Buffer* GetIndexBuffer() const { return DXIndexBuffer; }
		ID3D11Buffer** GetInitIndexBuffer() { return &DXIndexBuffer; }

	private:
		U32 Size;

		const U32* Buffer;

		ID3D11Buffer* DXIndexBuffer;

	};


	class DX11UniformBuffer : public RHIUniformBuffer
	{
	public:
		DX11UniformBuffer();

		DX11UniformBuffer(ID3D11Buffer*, U32 Size, const void*);

		virtual ~DX11UniformBuffer();

		const void* GetPointer() const { return Buffer; }

		U32 GetSize() const { return Size; }

		ID3D11Buffer* GetUniformBuffer() const { return DXConstantBuffer; }
		ID3D11Buffer** GetInitUniformBuffer() { return &DXConstantBuffer; }

	private:
		U32 Size;

		const void* Buffer;

		ID3D11Buffer* DXConstantBuffer;
	};
}
#endif // !DX11BUFFER_H
