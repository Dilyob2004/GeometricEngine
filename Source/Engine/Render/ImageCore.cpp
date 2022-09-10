#include <Engine/Render/ImageCore.h>



namespace MeteorEngine
{ 

	ImageCore::ImageCore():
		m_size(0, 0),
		m_channels(0),
		m_pointer()
	{

	}
	ImageCore::~ImageCore()
	{
		m_pointer.clear();
	}
	bool ImageCore::Load(const std::string& path)
	{
		return ImageLoader::Load(path, m_pointer, m_size, m_channels);
	}
	void ImageCore::FlipX()
	{

	}
	void ImageCore::FlipY()
	{

	}

}