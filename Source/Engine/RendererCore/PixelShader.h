#ifndef PIXELSHADER_H
#define PIXELSHADER_H
#include <Engine/RHI/DynamicRHI.h>
namespace GeometricEngine
{
	class PixelShader
	{
	public:
		PixelShader():
			PixelShaders()
		{
		}
		~PixelShader()
		{
			PixelShaders.Clear();
		}
		void AddRenderer(const TVector<U32>& Code)
		{
			PixelShaders.Push(GDynamicRHI->RHICreatePixelShader(Code));
		}
		RHIPixelShader* GetRefPixelShaderByIndex(I32 Index) const
		{
			return PixelShaders[Index];
		}
		void Tick()
		{
			for(RHIPixelShader* Shader : PixelShaders)
				GDynamicRHI->RHIBindPixelShader(Shader);
		}
	private:
		TVector<RHIPixelShader*> PixelShaders;
	};
}
#endif // !PIXELSHADER_H
