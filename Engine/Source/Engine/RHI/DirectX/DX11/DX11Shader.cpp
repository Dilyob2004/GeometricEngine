#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Shader.h>
#include <Engine/RHI/DirectX/DX11/DX11Utilities.h>
#include <Engine/RHI/DirectX/DX11/DX11Resources.h>
#include <Engine/Core/Misc/Log.h>
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

}