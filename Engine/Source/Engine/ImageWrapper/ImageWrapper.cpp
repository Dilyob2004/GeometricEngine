#include <Engine/ImageWrapper/ImageWrapper.h>

#define STB_IMAGE_IMPLEMENTATION
#include <ThirdParty/stb/stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

bool ImageWrapper::Load(const String& Path, TArray<U8>& OutputData, U32& Width, U32& Height)
{
	I32 OutWidth = 0, OutHeight = 0, Channels = 0;
	U8* Data = stbi_load(*Path, &OutWidth, &OutHeight, &Channels, STBI_rgb_alpha);

	if (Data)
	{
		Width = (U32)OutWidth;
		Height = (U32)OutHeight;

		OutputData.Resize(Width * Height * 4);
		SMemory::Copy(OutputData.Pointer(), Data, OutputData.Count());

		stbi_image_free(Data);

		return true;
	}

	return false;
}
