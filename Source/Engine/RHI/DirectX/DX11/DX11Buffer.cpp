#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Buffer.h>
#include <Engine/Platform/Platform.h>
namespace MeteorEngine
{

	DX11VertexBuffer::DX11VertexBuffer()
		: Size(0)
		, Buffer(NULL)
		, DXVertexBuffer(NULL)
			
	{
	}
	DX11VertexBuffer::DX11VertexBuffer(ID3D11Buffer* DXBuffer, u32 BufferSize, void* BufferPointer)
		: Size(BufferSize)
		, Buffer(BufferPointer)
		, DXVertexBuffer(DXBuffer)
	{
	}
	DX11VertexBuffer::~DX11VertexBuffer()
	{
		DXVertexBuffer->Release();
		delete[] Buffer;
		Buffer = NULL;
		Size = 0;

	}
	RHIVertexBuffer* DX11DynamicRHI::RHICreateVertexBuffer(void* Buffer, u32 Size)
	{
		ID3D11Buffer* DXBuffer = NULL;
		D3D11_BUFFER_DESC BufferDescriptor;
		Platform::Memzero(&BufferDescriptor, sizeof(BufferDescriptor));
		BufferDescriptor.BindFlags	= D3D11_BIND_VERTEX_BUFFER;
		BufferDescriptor.Usage		= D3D11_USAGE_DEFAULT;
		BufferDescriptor.ByteWidth	= Size;
		D3D11_SUBRESOURCE_DATA ResourceData;
		Platform::Memzero(&ResourceData, sizeof(ResourceData));
		ResourceData.pSysMem		= Buffer;
		ResourceData.SysMemPitch	= Size;
		D3D11_INPUT_ELEMENT_DESC desc;
		
		if (FAILED(DXDevice->CreateBuffer(&BufferDescriptor, &ResourceData, &DXBuffer)))
		{
			LOG("DX11 FAILED: CreateBuffer!");
			return NULL;
		}
		return new DX11VertexBuffer(DXBuffer, Size, Buffer);
	}

	void DX11DynamicRHI::RHIDrawVertices(u32 Count, u32 Start)
	{
		DXDeviceContext->Draw(Count, Start);
	}
	void DX11DynamicRHI::RHIBindVertexBuffer(const RHIVertexBuffer* VertexBuffer, u32 stride, u32 offset)
	{
		ID3D11Buffer* Buffer = ((DX11VertexBuffer*)VertexBuffer)->GetDXVertexBuffer();
		if (Buffer == NULL)
		{
			exit(-1);
		}
		DXDeviceContext->IASetVertexBuffers(0, 1, &Buffer, &stride, &offset);
	}
	RHIIndexBuffer* DX11DynamicRHI::RHICreateIndexBuffer(void* Buffer, u32 Size)
	{
		return NULL;
	}
}