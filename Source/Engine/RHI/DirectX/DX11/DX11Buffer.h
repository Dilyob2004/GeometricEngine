#ifndef DX11BUFFER_H
#define DX11BUFFER_H
#include <Engine/RHI/RHIResources.h>
#include <d3d11.h>
namespace GeometricEngine
{
	class DX11VertexBuffer : public RHIVertexBuffer
	{
	public:
		DX11VertexBuffer();

		DX11VertexBuffer(ID3D11Buffer* , U32 Size, void*);

		virtual ~DX11VertexBuffer();

		void* GetPointer() const  { return Buffer; }

		U32 GetSize() const  { return Size; }

		ID3D11Buffer* GetVertexBuffer() const { return DXVertexBuffer; }
		ID3D11Buffer** GetInitVertexBuffer() { return &DXVertexBuffer; }

	private:
		U32 Size;

		void* Buffer;

		ID3D11Buffer* DXVertexBuffer;

	};

	class DX11IndexBuffer : public RHIIndexBuffer
	{
	public:
		DX11IndexBuffer();

		DX11IndexBuffer(ID3D11Buffer*, U32 Size, U32*);

		virtual ~DX11IndexBuffer();

		U32* GetPointer() const { return Buffer; }

		U32 GetSize() const { return Size; }

		ID3D11Buffer* GetIndexBuffer() const { return DXIndexBuffer; }
		ID3D11Buffer** GetInitIndexBuffer() { return &DXIndexBuffer; }

	private:
		U32 Size;

		U32* Buffer;

		ID3D11Buffer* DXIndexBuffer;

	};


	class DX11ConstantBuffer : public RHIConstantBuffer
	{
	public:
		DX11ConstantBuffer();

		DX11ConstantBuffer(ID3D11Buffer*, U32 Size, void*);

		virtual ~DX11ConstantBuffer();

		void* GetPointer() const { return Buffer; }

		U32 GetSize() const { return Size; }

		ID3D11Buffer* GetConstantBuffer() const { return DXConstantBuffer; }
		ID3D11Buffer** GetInitConstantBuffer() { return &DXConstantBuffer; }

	private:
		U32 Size;

		void* Buffer;

		ID3D11Buffer* DXConstantBuffer;
	};
}
#endif // !DX11BUFFER_H
