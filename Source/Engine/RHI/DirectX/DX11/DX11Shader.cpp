#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <d3dcompiler.h>
namespace MeteorEngine
{
	DX11PixelShader::DX11PixelShader()
		: Code()
		, DXShader(NULL)
	{
	}	
	DX11PixelShader::DX11PixelShader(ID3D11PixelShader* Shader,const std::vector<u32>& pCode)
		: Code(pCode)
		, DXShader(Shader)
	{
	}
	DX11PixelShader::~DX11PixelShader()
	{
		Code.clear();
		DXShader = NULL;
	}

	DX11VertexShader::DX11VertexShader()
		: Code(NULL)
		, DXShader(NULL)
	{
	}	
	DX11VertexShader::DX11VertexShader(ID3D11VertexShader* Shader,const std::vector<u32>& pCode)
		: Code(pCode)
		, DXShader(Shader)
	{
	}
	DX11VertexShader::~DX11VertexShader()
	{
		Code.clear();
		DXShader = NULL;
	}
	DX11VertexLayout::DX11VertexLayout()
		: DXInputLayout(NULL)
	{

	}
	DX11VertexLayout::DX11VertexLayout(ID3D11InputLayout* InputLayout)
		: DXInputLayout(InputLayout)
	{

	}
	DX11VertexLayout::~DX11VertexLayout()
	{
		DXInputLayout->Release();
	}

	RHIPixelShader* DX11DynamicRHI::RHICreatePixelShader(const std::vector<u32>& Code)
	{
		ID3D11PixelShader* PixelShader = NULL;
		if (FAILED(DXDevice->CreatePixelShader(Code.data(), Code.size(), NULL, &PixelShader)))
		{
			LOG("Error: CreatePixelShader!");
			exit(-1);
		}
		return new DX11PixelShader(PixelShader, Code);
	}
	RHIVertexShader* DX11DynamicRHI::RHICreateVertexShader(const std::vector<u32>& Code)
	{
		ID3D11VertexShader* VertexShader = NULL;
		if(FAILED(DXDevice->CreateVertexShader(Code.data(), Code.size(), NULL, &VertexShader)))
		{
			LOG("Error: CreatePixelShader!");
			exit(-1);
		}
		return new DX11VertexShader(VertexShader, Code);
	}
	static DXGI_FORMAT BufferLaoutFormatDX11ToBufferLayoutFormatMeteor(ShaderElementType type)
	{
		switch (type)
		{
			case MeteorEngine::ShaderElementType::Int:
				break;
			case MeteorEngine::ShaderElementType::Int2:
				break;
			case MeteorEngine::ShaderElementType::Int3:
				break;
			case MeteorEngine::ShaderElementType::Int4:
				break;
			case MeteorEngine::ShaderElementType::Mat:
				break;
			case MeteorEngine::ShaderElementType::Mat2:
				break;
			case MeteorEngine::ShaderElementType::Mat3:
				break;
			case MeteorEngine::ShaderElementType::Mat4:
				break;
			case MeteorEngine::ShaderElementType::Float:	return DXGI_FORMAT_R32_FLOAT;
			case MeteorEngine::ShaderElementType::Float2:	return DXGI_FORMAT_R32G32_FLOAT;
			case MeteorEngine::ShaderElementType::Float3:	return DXGI_FORMAT_R32G32B32_FLOAT;
			case MeteorEngine::ShaderElementType::Float4:	return DXGI_FORMAT_R32G32B32A32_FLOAT;
			default: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
	}
	RHIVertexLayout* DX11DynamicRHI::RHICreateVertexLayout(const RHIVertexShader* VertexShader, const VertexLayoutGroup& LayoutGoup)
	{
		ID3D11InputLayout* DXInputLayout = NULL;
		std::vector<D3D11_INPUT_ELEMENT_DESC> InputElementsDescriptor;
		for (auto& Element : LayoutGoup)
		{
			InputElementsDescriptor.push_back({ Element.BufferName.c_str(),
									0,
									BufferLaoutFormatDX11ToBufferLayoutFormatMeteor(Element.BufferType),
									0,
									D3D11_APPEND_ALIGNED_ELEMENT,
									D3D11_INPUT_PER_VERTEX_DATA,
									0 });
		}
		if (FAILED(DXDevice->CreateInputLayout(InputElementsDescriptor.data(),
			InputElementsDescriptor.size(),
			((DX11VertexShader*)VertexShader)->GetPointerCode().data(),
			((DX11VertexShader*)VertexShader)->GetPointerCode().size(),
			&DXInputLayout)))
		{
			LOG("Error: CreateInputLayout!");
			exit(-1);
		}
		return new DX11VertexLayout(DXInputLayout);
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
		Code.resize(DXCode->GetBufferSize());
		memcpy(Code.data(), DXCode->GetBufferPointer(), Code.size());
		return (Result == S_OK);
	}
	RHIShaderCompiler* RHIShaderCompiler::StaticCreate()
	{
		return new DX11ShaderCompiler();
	}
}