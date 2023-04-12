#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <Engine/RHI/DirectX/DX11/DX11Buffer.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/Core/Generic/Memory.h>
#include <Engine/Core/Misc/Log.h>
namespace GeometricEngine
{

	DX11VertexBuffer::DX11VertexBuffer()
		: Size(0)
		, Buffer(NULL)
		, DXVertexBuffer(NULL)
	{
	}
	DX11VertexBuffer::DX11VertexBuffer(ID3D11Buffer* DXBuffer, U32 BufferSize, void* BufferPointer)
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
	RHIVertexBuffer* DX11DynamicRHI::RHICreateVertexBuffer(void* Buffer, U32 Size)
	{
		D3D11_BUFFER_DESC BufferDescriptor;
		SMemory::Zero(&BufferDescriptor, sizeof(BufferDescriptor));


		BufferDescriptor.BindFlags	= D3D11_BIND_VERTEX_BUFFER;
		BufferDescriptor.Usage		= D3D11_USAGE_DEFAULT;
		BufferDescriptor.ByteWidth	= Size;

		D3D11_SUBRESOURCE_DATA ResourceData;
		SMemory::Zero(&ResourceData, sizeof(ResourceData));
		ResourceData.pSysMem		= Buffer;
		ResourceData.SysMemPitch	= Size;
		
		ID3D11Buffer* DXBuffer = NULL;
		if (FAILED(DXDevice->CreateBuffer(&BufferDescriptor, &ResourceData, &DXBuffer)))
		{
			LOG("Error: [DX11RHI] Failed to Create a Vertex Buffer!");
			return NULL;
		}
		return new DX11VertexBuffer(DXBuffer, Size, Buffer);
	}


	DX11IndexBuffer::DX11IndexBuffer()
		: DXIndexBuffer(NULL)
		, Buffer(NULL)
		, Size(0)
	{

	}
	DX11IndexBuffer::DX11IndexBuffer(ID3D11Buffer* IndexBuffer, U32 BufferSize, U32* BufferPointer)
		: DXIndexBuffer(IndexBuffer)
		, Size(BufferSize)
		, Buffer(BufferPointer)
	{
	}
	DX11IndexBuffer::~DX11IndexBuffer()
	{
		DXIndexBuffer->Release();
		delete[] Buffer;
		Buffer = NULL;
	}
	RHIIndexBuffer* DX11DynamicRHI::RHICreateIndexBuffer(U32* Buffer, U32 Size)
	{
		
		D3D11_BUFFER_DESC BufferDescriptor;
		SMemory::Zero(&BufferDescriptor, sizeof(BufferDescriptor));

		BufferDescriptor.BindFlags = D3D11_BIND_INDEX_BUFFER;
		BufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
		BufferDescriptor.ByteWidth = Size;
		
		
		D3D11_SUBRESOURCE_DATA ResourceData;
		SMemory::Zero(&ResourceData, sizeof(ResourceData));

		ResourceData.pSysMem = Buffer;
		ResourceData.SysMemPitch = Size;

		ID3D11Buffer* DXBuffer = NULL;
		if (FAILED(DXDevice->CreateBuffer(&BufferDescriptor, &ResourceData, &DXBuffer)))
		{
			LOG("Error: [DX11RHI] Failed to Create a Index Buffer!");
			return NULL;
		}
		return new DX11IndexBuffer(DXBuffer, Size, Buffer);
	}

	


	DX11ConstantBuffer::DX11ConstantBuffer()
		: DXConstantBuffer(NULL)
		, Buffer(NULL)
		, Size(0)
	{

	}
	DX11ConstantBuffer::DX11ConstantBuffer(ID3D11Buffer* ConstantBuffer, U32 BufferSize, void* BufferPointer)
		: DXConstantBuffer(ConstantBuffer)
		, Size(BufferSize)
		, Buffer(BufferPointer)
	{
	}
	DX11ConstantBuffer::~DX11ConstantBuffer()
	{
		DXConstantBuffer->Release();
		delete[] Buffer;
		Buffer = NULL;
	}

	RHIConstantBuffer* DX11DynamicRHI::RHICreateConstantBuffer(void* Buffer, U32 Size)
	{

		D3D11_BUFFER_DESC BufferDescriptor;
		SMemory::Zero(&BufferDescriptor, sizeof(BufferDescriptor));
		BufferDescriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		BufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
		BufferDescriptor.ByteWidth = Size;

		D3D11_SUBRESOURCE_DATA ResourceData;
		SMemory::Zero(&ResourceData, sizeof(ResourceData));

		ResourceData.pSysMem = Buffer;
		ResourceData.SysMemPitch = Size;

		ID3D11Buffer* DXBuffer = NULL;
		if (FAILED(DXDevice->CreateBuffer(&BufferDescriptor, &ResourceData, &DXBuffer)))
		{
			LOG("Error: [DX11RHI] Failed to Create a Constant Buffer!");
			return NULL;
		}
		return new DX11ConstantBuffer(DXBuffer, Size, Buffer);
	}

}