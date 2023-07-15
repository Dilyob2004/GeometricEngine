#ifndef DX11SHADER_H
#define DX11SHADER_H
#include <Engine/Core/Config.h>
#include <Engine/RHI/RHIResources.h>
#include <d3d11.h>

class DX11PixelShader : public RHIPixelShader
{
public:
	DX11PixelShader();
	DX11PixelShader(ID3D11PixelShader*, const TArray<U32>&);
	virtual ~DX11PixelShader();
	ID3D11PixelShader* GetShader() const { return DXShader; }
	const TArray<U32>& GetCode() const { return Code; }
private:
	ID3D11PixelShader* DXShader;
	TArray<U32> Code;
};

class DX11VertexShader : public RHIVertexShader
{
public:
	DX11VertexShader();
	DX11VertexShader(ID3D11VertexShader*, const TArray<U32>&);
	virtual ~DX11VertexShader();
	ID3D11VertexShader* GetShader() const { return DXShader; }
	const TArray<U32>& GetCode() const { return Code; }
private:
	ID3D11VertexShader* DXShader;
	TArray<U32> Code;
};

#endif // !DX11SHADER_H
