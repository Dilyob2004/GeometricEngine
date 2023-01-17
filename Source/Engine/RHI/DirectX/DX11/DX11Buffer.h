#ifndef DX11BUFFER_H
#define DX11BUFFER_H
#include <Engine/RHI/RHIResources.h>
#include <d3d11.h>
namespace MeteorEngine
{
	class DX11VertexBuffer : public RHIVertexBuffer
	{
	public:
		DX11VertexBuffer();
		DX11VertexBuffer(ID3D11Buffer* ,u32 Size, void*);
		virtual ~DX11VertexBuffer();
		virtual void* GetPointer() const override { return Buffer; }
		virtual u32 GetSize() const override { return Size; }
		ID3D11Buffer* GetDXVertexBuffer() const { return DXVertexBuffer; }
	private:
		u32 Size;
		void* Buffer;
		ID3D11Buffer* DXVertexBuffer;
	};
	class DX11IndexBuffer : public RHIIndexBuffer
	{
	public:
		virtual ~DX11IndexBuffer();
		virtual u32* GetPointer() const override;
		virtual u32 GetSize() const override;
		ID3D11Buffer* GetDXIndexBuffer() const { return DXIndexBuffer; }
	private:
		u32 Size;
		void* Buffer;
		ID3D11Buffer* DXIndexBuffer;
	};
}
#endif // !DX11BUFFER_H
