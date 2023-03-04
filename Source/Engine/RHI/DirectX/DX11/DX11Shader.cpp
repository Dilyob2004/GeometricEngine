#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <Engine/Core/Misc/Log.h>
#include <d3dcompiler.h>
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
		DXShader = NULL;
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
		DXShader = NULL;
	}
	DX11VertexLayout::DX11VertexLayout()
		: DXInputLayout(NULL)
		, VertexLayout()
	{

	}
	DX11VertexLayout::DX11VertexLayout(ID3D11InputLayout* InputLayout, const VertexLayoutGroup& LayoutGoup)
		: DXInputLayout(InputLayout)
		, VertexLayout(LayoutGoup)
	{

	}
	DX11VertexLayout::~DX11VertexLayout()
	{
		DXInputLayout->Release();
	}

	RHIPixelShader* DX11DynamicRHI::RHICreatePixelShader(const TVector<U32>& Code)
	{
		ID3D11PixelShader* PixelShader = NULL;
		if (FAILED(DXDevice->CreatePixelShader(Code.Pointer(), Code.GetSize(), NULL, &PixelShader)))
		{
			LOG("Error: [DirectX 11] Failed to Create a Pixel Shader!");
			exit(-1);
		}
		return new DX11PixelShader(PixelShader, Code);
	}
	RHIVertexShader* DX11DynamicRHI::RHICreateVertexShader(const TVector<U32>& Code)
	{
		ID3D11VertexShader* VertexShader = NULL;
		if(FAILED(DXDevice->CreateVertexShader(Code.Pointer(), Code.GetSize(), NULL, &VertexShader)))
		{
			LOG("Error: [DirectX 11] Failed to Create a Vertex Shader!");
			exit(-1);
		}
		return new DX11VertexShader(VertexShader, Code);
	}
	static DXGI_FORMAT BufferLaoutFormatDX11ToBufferLayoutFormatMeteor(ShaderElementType type)
	{
		switch (type)
		{
			case ShaderElementType::Int:		return DXGI_FORMAT_R32_SINT;
			case ShaderElementType::Int2:		return DXGI_FORMAT_R32G32_SINT;
			case ShaderElementType::Int3:		return DXGI_FORMAT_R32G32B32_SINT;
			case ShaderElementType::Int4:		return DXGI_FORMAT_R32G32B32A32_SINT;
			case ShaderElementType::Float:	return DXGI_FORMAT_R32_FLOAT;
			case ShaderElementType::Float2:	return DXGI_FORMAT_R32G32_FLOAT;
			case ShaderElementType::Float3:	return DXGI_FORMAT_R32G32B32_FLOAT;
			case ShaderElementType::Float4:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
			default: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
	}
	RHIVertexLayout* DX11DynamicRHI::RHICreateVertexLayout(const RHIVertexShader* VertexShader, const VertexLayoutGroup& LayoutGoup)
	{
		ID3D11InputLayout* DXInputLayout = NULL;
		TVector<D3D11_INPUT_ELEMENT_DESC> InputElementsDescriptor;
		bool IsFirstElement = true;
		for (auto& Element : LayoutGoup.GetVertexGroup())
		{
			InputElementsDescriptor.Push({ Element.BufferName.Pointer(),
									0,
									BufferLaoutFormatDX11ToBufferLayoutFormatMeteor(Element.BufferType),
									0,
									(IsFirstElement) ? 0 : D3D11_APPEND_ALIGNED_ELEMENT,
									D3D11_INPUT_PER_VERTEX_DATA,
									0 });

			if (IsFirstElement) IsFirstElement = false;
		}
		if (FAILED(DXDevice->CreateInputLayout(	InputElementsDescriptor.Pointer(),
												InputElementsDescriptor.GetCount(),
												((DX11VertexShader*)VertexShader)->GetPointerCode().Pointer(),
												((DX11VertexShader*)VertexShader)->GetPointerCode().GetCount(),
												&DXInputLayout)))
		{
			LOG("Error:[DirectX 11] Failed to Create a InputLayout!");
			exit(-1);
		}
		return new DX11VertexLayout(DXInputLayout, LayoutGoup);
	}
	void DX11DynamicRHI::RHIBindPixelShader(const RHIPixelShader* PixelShader)
	{
		DXDeviceContext->PSSetShader(((DX11PixelShader*)PixelShader)->GetDXShader(), NULL, 0);
	}
	void DX11DynamicRHI::RHIBindVertexShader(const RHIVertexShader* VertexShader)
	{
		DXDeviceContext->VSSetShader(((DX11VertexShader*)VertexShader)->GetDXShader(), NULL, 0);
	}
	void DX11DynamicRHI::RHIBindVertexLayout(const RHIVertexLayout* VertexLayout)
	{
		DXDeviceContext->IASetInputLayout(((DX11VertexLayout*)VertexLayout)->GetDXInputLayout());
	}

	DX11ShaderCompiler::DX11ShaderCompiler()
		: Code()
	{
	}
	DX11ShaderCompiler::~DX11ShaderCompiler()
	{
	}

	bool DX11ShaderCompiler::Compile(	const WCHAR* Path,
										const CHAR* EntryPoint,
										const CHAR* Target)
	{
		ID3DBlob* DXCode = NULL;
		ID3DBlob* DXErrors = NULL;
		
		HRESULT Result = D3DCompileFromFile(Path,
											NULL,
											D3D_COMPILE_STANDARD_FILE_INCLUDE,
											EntryPoint,
											Target,
											D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG,
											0,
											&DXCode,
											&DXErrors
											);
		if(DXErrors != NULL)
			if (DXErrors->GetBufferSize() > 0)
			{
				TVector<char> ErrorCode(static_cast<I32>(DXErrors->GetBufferSize()));
				SMemory::Copy(ErrorCode.Pointer(), DXErrors->GetBufferPointer(), ErrorCode.GetCount());
				for (auto i : ErrorCode)
					std::clog << i;


				exit(-1);
			}
		
		Code.Resize(static_cast<I32>(DXCode->GetBufferSize()));
		SMemory::Copy(Code.Pointer(), DXCode->GetBufferPointer(), Code.GetCount());
		return (Result == S_OK);
	}
	RHIShaderCompiler* RHIShaderCompiler::StaticCreate()
	{
		return new DX11ShaderCompiler();
	}
}