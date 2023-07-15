#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <Engine/RHI/DirectX/DX11/DX11Buffer.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/Core/Generic/Memory.h>
#include <Engine/Core/Misc/Log.h>

RHIVertexBuffer* DX11DynamicRHI::RHICreateVertexBuffer(const void* Data, U32 Size, U32 Stride, U32 Offset, RHIUsage Usage)
{
	D3D11_BUFFER_DESC BufferDescriptor;
	SMemory::Zero(&BufferDescriptor, sizeof(BufferDescriptor));

	BufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDescriptor.CPUAccessFlags = (Usage == RHIUsage::Dynamic) ? D3D11_CPU_ACCESS_WRITE : 0;
	BufferDescriptor.Usage = EngineUsageToDX11(Usage);
	BufferDescriptor.ByteWidth = Size;

	D3D11_SUBRESOURCE_DATA ResourceData;
	SMemory::Zero(&ResourceData, sizeof(ResourceData));
	ResourceData.pSysMem = Data;
	ResourceData.SysMemPitch = Size;

	ID3D11Buffer* DXBuffer = NULL;
	if (FAILED(DXDevice->CreateBuffer(&BufferDescriptor, &ResourceData, &DXBuffer)))
	{
		LOG("Error: [DX11RHI] Failed to Create a Vertex Buffer!\n");
		return NULL;
	}
	return new DX11VertexBuffer(DXBuffer, Data, Size, Stride, Offset);
}




RHIIndexBuffer* DX11DynamicRHI::RHICreateIndexBuffer(const U32* Buffer, U32 Size, RHIUsage Usage)
{
		
	D3D11_BUFFER_DESC BufferDescriptor;
	SMemory::Zero(&BufferDescriptor, sizeof(BufferDescriptor));

	BufferDescriptor.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferDescriptor.CPUAccessFlags = (Usage == RHIUsage::Dynamic) ? D3D11_CPU_ACCESS_WRITE : 0;
	BufferDescriptor.ByteWidth = Size;
		
		
	D3D11_SUBRESOURCE_DATA ResourceData;
	SMemory::Zero(&ResourceData, sizeof(ResourceData));

	ResourceData.pSysMem = Buffer;
	ResourceData.SysMemPitch = Size;

	ID3D11Buffer* DXBuffer = NULL;
	if (FAILED(DXDevice->CreateBuffer(&BufferDescriptor, &ResourceData, &DXBuffer)))
	{
		LOG("Error: [DX11RHI] Failed to Create a Index Buffer!\n");
		return NULL;
	}
	return new DX11IndexBuffer(DXBuffer, Size, Buffer);
}


RHIUniformBuffer* DX11DynamicRHI::RHICreateUniformBuffer(const void* Buffer, U32 Size, RHIUsage Usage)
{

	D3D11_BUFFER_DESC BufferDescriptor;
	SMemory::Zero(&BufferDescriptor, sizeof(BufferDescriptor));
	BufferDescriptor.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDescriptor.CPUAccessFlags = (Usage == RHIUsage::Dynamic) ? D3D11_CPU_ACCESS_WRITE : 0;
	BufferDescriptor.Usage = EngineUsageToDX11(Usage);
	BufferDescriptor.ByteWidth = Size;
		
	D3D11_SUBRESOURCE_DATA ResourceData;
	SMemory::Zero(&ResourceData, sizeof(ResourceData));

	ResourceData.pSysMem = Buffer;
	ResourceData.SysMemPitch = Size;

	ID3D11Buffer* DXBuffer = NULL;
	if (FAILED(DXDevice->CreateBuffer(&BufferDescriptor, &ResourceData, &DXBuffer)))
	{
		LOG("Error: [DX11RHI] Failed to Create a Uniform Buffer!\n");
		return NULL;
	}
	return new DX11UniformBuffer(DXBuffer, Size, Buffer);
}

