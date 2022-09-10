#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include <Engine/Core/Config.h>
#include <Engine/Math/Vector2.h>
#include <vector>
namespace MeteorEngine
{
	class METEOR_API ImageLoader
	{
	public:
		ImageLoader() = default;
		~ImageLoader() = default;
		static bool Load(const std::string&, std::vector<u8>&, Vector2u&, s32&);
		//static bool Write(const std::string&, std::vector<u8>&, Vector2u&);
	};
}

#endif // !IMAGELOADER_H
