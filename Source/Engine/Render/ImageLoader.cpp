#include <Engine/Render/ImageLoader.h>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION

#include <stb_image/stb_image.h>

#ifdef STB_IMAGE_IMPLEMENTATION
#undef STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION

namespace MeteorEngine
{
	bool ImageLoader::Load(const std::string& path, std::vector<u8>& pointer, Vector2u& size, s32 &channels)
	{
		s32 w = 0, h = 0, c = 0;

		u8* data = stbi_load(path.c_str(), &w, &h, &c, 0);

		if (data)
		{
			size.x = static_cast<u32>(w);
			size.y = static_cast<u32>(h);
			channels = c;
			pointer.resize(static_cast<std::size_t>(w * h * 4));

			memcpy(pointer.data(), data, pointer.size());

			stbi_image_free(data);
			return true;
		}


		return false;
	}
}