#pragma once


#include <Engine/ImageCore/ImageCore.h>
#include <Engine/RHI/DynamicRHI.h>

class GEOMETRIC_API FSprite
{
public:

	FSprite();
	FSprite(const String&);
	~FSprite();

	void Init(const String&);
	void OnResize(U32, U32);

	void Release();

	RHITexture2D* GetTextureRHI() { return Texture; }
	String GetPath() const { return Path; }
private:
	String Path;
	Image ImageData;
	RHITexture2D* Texture;
};