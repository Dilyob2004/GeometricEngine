#ifndef DX11BUFFER_H
#define DX11BUFFER_H
#include <Engine/RHI/RHIResources.h>
#include <d3d11.h>
namespace GeometricEngine
{
	class  DX11VertexBuffer : public RHIVertexBuffer
	{
	public:
		DX11VertexBuffer();

		DX11VertexBuffer(ID3D11Buffer* , U32 Size, void*);

		virtual ~DX11VertexBuffer();

		virtual void* GetPointer() const override { return Buffer; }

		virtual U32 GetSize() const override { return Size; }

		ID3D11Buffer* GetDXVertexBuffer() const { return DXVertexBuffer; }

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

		virtual U32* GetPointer() const override { return Buffer; }

		virtual U32 GetSize() const override { return Size; }

		ID3D11Buffer* GetDXIndexBuffer() const { return DXIndexBuffer; }

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

		~DX11ConstantBuffer();

		virtual void* GetPointer() const override { return Buffer; }

		virtual U32 GetSize() const override { return Size; }

		ID3D11Buffer* GetDXConstantBuffer() const { return DXConstantBuffer; }

	private:
		U32 Size;

		void* Buffer;

		ID3D11Buffer* DXConstantBuffer;
	};
}
#endif // !DX11BUFFER_H
