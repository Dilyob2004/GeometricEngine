#include "TextureResource2D.h"


namespace GeometricEngine
{

	TextureResource2D::TextureResource2D()
		: Texture(NULL)
		, SamplerState(NULL)
		, BoundState(NULL)
	{

	}
	TextureResource2D::TextureResource2D(const RHITextureDefinition& TextureDef,
		const RHISamplerStateDefinition& SamplerDef,
		 BoundShaderResource* ShaderState)
	{
		BoundState = ShaderState;

		Texture = GDynamicRHI->RHICreateTexture2D(TextureDef);

		SamplerState = GDynamicRHI->RHICreateSamplerState(SamplerDef);
	}
	TextureResource2D::~TextureResource2D()
	{

	}
	void TextureResource2D::OnTick()
	{
		BoundState->OnTick();
		GDynamicRHI->RHISetTexture(BoundState->GetPixelShader(), Texture);
		GDynamicRHI->RHISetSamplerState(BoundState->GetPixelShader(), SamplerState);
	}
}