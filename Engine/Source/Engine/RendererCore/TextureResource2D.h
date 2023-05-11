#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H
#include "ShaderResource.h"
namespace GeometricEngine
{
	class GEOMETRIC_API TextureResource2D
	{
	public:
		TextureResource2D();
		TextureResource2D(const RHITextureDefinition& TextureDef,
						  const RHISamplerStateDefinition& SamplerDef);
		~TextureResource2D();

		void OnTick(const TSharedPtr<BoundShaderResource>&);
	private:
		RHITexture2D* Texture;
		RHISamplerState* SamplerState;
	};
}
#endif // !TEXTURERESOURCE_H
