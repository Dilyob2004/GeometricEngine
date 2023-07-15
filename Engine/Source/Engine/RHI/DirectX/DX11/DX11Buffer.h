#ifndef DX11BUFFER_H
#define DX11BUFFER_H
#include <Engine/RHI/RHIResources.h>
#include <d3d11.h>

class DX11VertexBuffer : public RHIVertexBuffer
{
public:
	DX11VertexBuffer()
		: Data(NULL)
		, Size(0)
		, Stride(0)
		, Offset(0)
		, DXVertexBuffer(NULL)
	{
	}

	DX11VertexBuffer(ID3D11Buffer* DXBuffer, const void* InData, U32 InSize, U32 InStride, U32 InOffset)
		: DXVertexBuffer(DXBuffer)
		, Data(InData)
		, Size(InSize)
		, Stride(InStride)
		, Offset(InOffset)
	{
	}
	virtual ~DX11VertexBuffer()
	{
		DXVertexBuffer->Release();
		delete[] Data;
		Data = NULL;
	}


	const void* GetData() { return Data; }
	U32 GetSize() const{ return Size; }
	U32 GetStride() const { return Stride; }
	U32 GetOffset() const { return Offset; }

	ID3D11Buffer* GetVertexBuffer() const { return DXVertexBuffer; }
	ID3D11Buffer** GetInitVertexBuffer() { return &DXVertexBuffer; }

private:

	const void* Data;
	U32 Size;
	U32 Stride;
	U32 Offset;

	ID3D11Buffer* DXVertexBuffer;

};

class DX11IndexBuffer : public RHIIndexBuffer
{
public:
	DX11IndexBuffer()
		: DXIndexBuffer(NULL)
		, Buffer(NULL)
		, Size(0)
	{

	}
	DX11IndexBuffer(ID3D11Buffer* IndexBuffer, U32 BufferSize, const U32* BufferPointer)
		: DXIndexBuffer(IndexBuffer)
		, Size(BufferSize)
		, Buffer(BufferPointer)
	{
	}

	virtual ~DX11IndexBuffer()
	{
		DXIndexBuffer->Release();
		delete [] Buffer;
		Buffer = NULL;
	}

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
	DX11UniformBuffer()
		: DXConstantBuffer(NULL)
		, Buffer(NULL)
		, Size(0)
	{

	}

	DX11UniformBuffer(ID3D11Buffer* ConstantBuffer, U32 BufferSize, const void* BufferPointer)
		: DXConstantBuffer(ConstantBuffer)
		, Size(BufferSize)
		, Buffer(BufferPointer)
	{
	}

	virtual ~DX11UniformBuffer()
	{
		DXConstantBuffer->Release();
		delete[] Buffer;
		Buffer = NULL;
	}

	const void* GetPointer() const { return Buffer; }

	U32 GetSize() const { return Size; }

	ID3D11Buffer* GetUniformBuffer() const { return DXConstantBuffer; }
	ID3D11Buffer** GetInitUniformBuffer() { return &DXConstantBuffer; }

private:
	U32 Size;

	const void* Buffer;

	ID3D11Buffer* DXConstantBuffer;
};

#endif // !DX11BUFFER_H
