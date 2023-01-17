#ifndef DX11SHADER_H
#define DX11SHADER_H
#include <Engine/Core/Config.h>
#include <Engine/RHI/RHIResources.h>
#include <d3d11.h>
namespace MeteorEngine
{
	class METEOR_API DX11PixelShader : public RHIPixelShader
	{
	public:
		DX11PixelShader();
		DX11PixelShader(ID3D11PixelShader*, const std::vector<u32>&);
		virtual ~DX11PixelShader();
		ID3D11PixelShader* GetDXShader() const { return DXShader; }
		const std::vector<u32>& GetPointerCode() const { return Code; }
	private:
		ID3D11PixelShader* DXShader;
		std::vector<u32> Code;
	};
	class METEOR_API DX11VertexShader : public RHIVertexShader
	{
	public:
		DX11VertexShader();
		DX11VertexShader(ID3D11VertexShader*, const std::vector<u32>&);
		virtual ~DX11VertexShader();
		ID3D11VertexShader* GetDXShader() const { return DXShader; }
		const std::vector<u32>& GetPointerCode() const { return Code; }
	private:
		ID3D11VertexShader* DXShader;
		std::vector<u32> Code;
	};
	class METEOR_API DX11VertexLayout : public RHIVertexLayout
	{
	public:
		DX11VertexLayout();
		DX11VertexLayout(ID3D11InputLayout* );
		virtual ~DX11VertexLayout();

		ID3D11InputLayout* GetDXInputLayout() const { return DXInputLayout; }
	private:
		ID3D11InputLayout* DXInputLayout;
	};
	class METEOR_API DX11ShaderCompiler: public RHIShaderCompiler
	{
	public:
		DX11ShaderCompiler();
		virtual ~DX11ShaderCompiler();
		virtual bool Compile(	const WCHAR* Path, 
								const CHAR* EntryPoint,
								const CHAR* Target) override;
		virtual const std::vector<u32>& GetResultCode() const override { return Code; }
	private:
		std::vector<u32> Code;
	};

}

#endif // !DX11SHADER_H
