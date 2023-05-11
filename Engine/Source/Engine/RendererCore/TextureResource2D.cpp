#include "TextureResource2D.h"


namespace GeometricEngine
{

	TextureResource2D::TextureResource2D()
		: Texture(NULL)
		, SamplerState(NULL)
	{

	}
	TextureResource2D::TextureResource2D(const RHITextureDefinition& TextureDef,
		const RHISamplerStateDefinition& SamplerDef)
	{

		Texture = GDynamicRHI->RHICreateTexture2D(TextureDef);

		SamplerState = GDynamicRHI->RHICreateSamplerState(SamplerDef);
	}
	TextureResource2D::~TextureResource2D()
	{

	}
	void TextureResource2D::OnTick(const TSharedPtr<BoundShaderResource>& BoundState)
	{
		GDynamicRHI->RHISetTexture(BoundState->GetPixelShader(), Texture);
		GDynamicRHI->RHISetSamplerState(BoundState->GetPixelShader(), SamplerState);
	}
}