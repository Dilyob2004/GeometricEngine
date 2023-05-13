#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <Engine/RHI/DirectX/DX11/DX11Buffer.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/Core/Generic/Memory.h>
#include <Engine/Core/Misc/Log.h>
namespace GeometricEngine
{

	DX11VertexBuffer::DX11VertexBuffer()
		: BufferView()
		, DXVertexBuffer(NULL)
	{
	}
	DX11VertexBuffer::DX11VertexBuffer(ID3D11Buffer* DXBuffer, const VertexBufferView& VBufferView)
		: DXVertexBuffer(DXBuffer)
		, BufferView(VBufferView)
	{
	}
	DX11VertexBuffer::~DX11VertexBuffer()
	{
		DXVertexBuffer->Release();
	}

	RHIVertexBuffer* DX11DynamicRHI::RHICreateVertexBuffer(const void* Data, U32 Size, U32 Stride, U32 Offset)
	{
		D3D11_BUFFER_DESC BufferDescriptor;
		SMemory::Zero(&BufferDescriptor, sizeof(BufferDescriptor));

		BufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		BufferDescriptor.Usage = D3D11_USAGE_DEFAULT;
		BufferDescriptor.ByteWidth = Size;

		D3D11_SUBRESOURCE_DATA ResourceData;
		SMemory::Zero(&ResourceData, sizeof(ResourceData));
		ResourceData.pSysMem = Data;
		ResourceData.SysMemPitch = Size;

		ID3D11Buffer* DXBuffer = NULL;
		if (FAILED(DXDevice->CreateBuffer(&BufferDescriptor, &ResourceData, &DXBuffer)))
		{
			LOG("Error: [DX11RHI] Failed to Create a Vertex Buffer!");
			return NULL;
		}
		VertexBufferView BufferView;
		BufferView.Data = Data;
		BufferView.Size = Size;
		BufferView.Stride = Stride;
		BufferView.Offset = Offset;
		return new DX11VertexBuffer(DXBuffer, BufferView);
	}


	DX11IndexBuffer::DX11IndexBuffer()
		: DXIndexBuffer(NULL)
		, Buffer(NULL)
		, Size(0)
	{

	}
	DX11IndexBuffer::DX11IndexBuffer(ID3D11Buffer* IndexBuffer, U32 BufferSize, const U32* BufferPointer)
		: DXIndexBuffer(IndexBuffer)
		, Size(BufferSize)
		, Buffer(BufferPointer)
	{
	}
	DX11IndexBuffer::~DX11IndexBuffer()
	{
		DXIndexBuffer->Release();
	}
	RHIIndexBuffer* DX11DynamicRHI::RHICreateIndexBuffer(const U32* Buffer, U32 Size)
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

	


	DX11UniformBuffer::DX11UniformBuffer()
		: DXConstantBuffer(NULL)
		, Buffer(NULL)
		, Size(0)
	{

	}
	DX11UniformBuffer::DX11UniformBuffer(ID3D11Buffer* ConstantBuffer, U32 BufferSize, const void* BufferPointer)
		: DXConstantBuffer(ConstantBuffer)
		, Size(BufferSize)
		, Buffer(BufferPointer)
	{
	}
	DX11UniformBuffer::~DX11UniformBuffer()
	{
		DXConstantBuffer->Release();
	}

	RHIUniformBuffer* DX11DynamicRHI::RHICreateUniformBuffer(void* Buffer, U32 Size)
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
			LOG("Error: [DX11RHI] Failed to Create a Uniform Buffer!");
			return NULL;
		}
		return new DX11UniformBuffer(DXBuffer, Size, Buffer);
	}

}