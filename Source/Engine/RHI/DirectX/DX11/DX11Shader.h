#ifndef DX11SHADER_H
#define DX11SHADER_H
#include <Engine/Core/Config.h>
#include <Engine/RHI/RHIResources.h>
#include <d3d11.h>
namespace GeometricEngine
{

	class DX11VertexLayout : public RHIVertexLayout
	{
	public:
		DX11VertexLayout();
		DX11VertexLayout(ID3D11InputLayout*, const TVector<BufferElement>&, U32);
		virtual ~DX11VertexLayout();

		virtual U32 GetStrideLayout() override { return Stride; }
		ID3D11InputLayout* GetDXInputLayout() const { return DXInputLayout; }
	private:
		ID3D11InputLayout* DXInputLayout;
		TVector<BufferElement> VertexLayout;
		U32 Stride;
	};


	class DX11PixelShader : public RHIPixelShader
	{
	public:
		DX11PixelShader();
		DX11PixelShader(ID3D11PixelShader*, const TVector<U32>&);
		virtual ~DX11PixelShader();
		ID3D11PixelShader* GetDXShader() const { return DXShader; }
		const TVector<U32>& GetPointerCode() const { return Code; }
	private:
		ID3D11PixelShader* DXShader;
		TVector<U32> Code;
	};

	class DX11VertexShader : public RHIVertexShader
	{
	public:
		DX11VertexShader();
		DX11VertexShader(ID3D11VertexShader*, const TVector<U32>&);
		virtual ~DX11VertexShader();
		ID3D11VertexShader* GetDXShader() const { return DXShader; }
		const TVector<U32>& GetPointerCode() const { return Code; }
	private:
		ID3D11VertexShader* DXShader;
		TVector<U32> Code;
	};

}

#endif // !DX11SHADER_H
