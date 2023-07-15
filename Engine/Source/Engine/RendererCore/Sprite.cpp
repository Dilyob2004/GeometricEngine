#include <Engine/RendererCore/Sprite.h>
#include <Engine/Core/Misc/Log.h>
#include <Engine/ShaderCompiler/ShaderCompilerWorker.h>



FSprite::FSprite()
	: Texture(NULL)
{

}
FSprite::FSprite(const String& Path)
	: Texture(NULL)
{
	Init(Path);
}
FSprite::~FSprite()
{
	Release();
}
void FSprite::Init(const String& InPath)
{
	Path = InPath;
	if (!ImageData.Load(Path))
		LOG("Warning: [IMAGE] Failed to Load Image");


	RHITextureDefinition TextureDef;
	TextureDef.Width = ImageData.GetWidth();
	TextureDef.Height = ImageData.GetHeight();
	TextureDef.Format = RHIPixelFormat::R8G8BA8_UNORM;
	Texture = GDynamicRHI->RHICreateTexture2D(TextureDef, ImageData.GetRawData());
}
void FSprite::OnResize(U32 Width, U32 Height)
{
	Release();
}
void FSprite::Release()
{
	Texture->SafeRelease();
}