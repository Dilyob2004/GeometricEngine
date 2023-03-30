#include <Engine/ImageCore/ImageCore.h>
#include <Engine/ImageWrapper/ImageWrapper.h>


namespace GeometricEngine
{

	Image::Image()
		: Width(0)
		, Height(0)
		, Data()
	{
	}	
	Image::Image(const Image& Copy)
		: Width(Copy.Width)
		, Height(Copy.Height)
		, Data(Copy.Data)
	{
	}
	Image::~Image()
	{
		Data.Clear();
	}
	bool Image::Load(const String& Path)
	{
		return ImageWrapper::Load(Path, Data, Width, Height);
	}
}