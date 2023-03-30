#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/RHI/DirectX/DX11/DX11Resources.h>
namespace GeometricEngine
{
	DX11PixelShader::DX11PixelShader()
		: Code()
		, DXShader(NULL)
	{
	}	
	DX11PixelShader::DX11PixelShader(ID3D11PixelShader* Shader,const TVector<U32>& pCode)
		: Code(pCode)
		, DXShader(Shader)
	{
	}
	DX11PixelShader::~DX11PixelShader()
	{
		Code.Clear();
		DXShader->Release();
	}

	DX11VertexShader::DX11VertexShader()
		: Code(NULL)
		, DXShader(NULL)
	{
	}	
	DX11VertexShader::DX11VertexShader(ID3D11VertexShader* Shader,const TVector<U32>& pCode)
		: Code(pCode)
		, DXShader(Shader)
	{
	}
	DX11VertexShader::~DX11VertexShader()
	{
		Code.Clear();
		DXShader->Release();
	}
	DX11VertexLayout::DX11VertexLayout()
		: DXInputLayout(NULL)
		, VertexLayout()
		, Stride(0)
	{

	}
	DX11VertexLayout::DX11VertexLayout(ID3D11InputLayout* InputLayout, const TVector<BufferElement>& LayoutGoup, U32 InStride)
		: DXInputLayout(InputLayout)
		, VertexLayout(LayoutGoup)
		, Stride(InStride)
	{

	}
	DX11VertexLayout::~DX11VertexLayout()
	{
		DXInputLayout->Release();
	}

	RHIPixelShader* DX11DynamicRHI::RHICreatePixelShader(const TVector<U32>& Code)
	{
		ID3D11PixelShader* PixelShader = NULL;
		if (FAILED(DXDevice->CreatePixelShader(Code.Pointer(), Code.GetCount(), NULL, &PixelShader)))
		{
			LOG("Error: [DX11RHI] Failed to Create a Pixel Shader!");
			exit(-1);
		}
		return new DX11PixelShader(PixelShader, Code);
	}
	RHIVertexShader* DX11DynamicRHI::RHICreateVertexShader(const TVector<U32>& Code)
	{
		ID3D11VertexShader* VertexShader;
		if(FAILED(DXDevice->CreateVertexShader(Code.Pointer(), Code.GetCount(), NULL, &VertexShader)))
		{
			LOG("Error: [DX11RHI] Failed to Create a Vertex Shader!");
			exit(-1);
		}
		return  new DX11VertexShader(VertexShader, Code);
	}
	RHIVertexLayout* DX11DynamicRHI::RHICreateVertexLayout(const RHIVertexShader* VertexShaderRHI, const TVector<BufferElement>& LayoutGoup)
	{
		DYNAMIC_CAST(DX11VertexShader, VertexShader, VertexShaderRHI);
		U32 Stride = 0;
		for (auto Element : LayoutGoup)
			Stride += GetShaderStrideType(Element.BufferType) * GetSizeOfShaderType(Element.BufferType);



		bool IsFirstElement = true;
		TVector<D3D11_INPUT_ELEMENT_DESC> InputElementsDescriptor;
		for (auto Element : LayoutGoup)
		{
			InputElementsDescriptor.Push({ Element.BufferName.Pointer(), 0, EngineFormatToDX11Format(Element.BufferType), 0,
									(IsFirstElement) ? 0 : D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });

			if (IsFirstElement) IsFirstElement = false;
		}
		ID3D11InputLayout* DXInputLayout;
		if (FAILED(DXDevice->CreateInputLayout(	InputElementsDescriptor.Pointer(),
												InputElementsDescriptor.GetCount(),
												VertexShader->GetCode().Pointer(),
												VertexShader->GetCode().GetCount(),
												&DXInputLayout)))
		{
			LOG("Error: [DX11RHI] Failed to Create a InputLayout!");
			exit(-1);
		}
		return new DX11VertexLayout(DXInputLayout, LayoutGoup, Stride);
	}



}