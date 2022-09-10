#ifndef IMAGECORE_H
#define IMAGECORE_H

#include <Engine/Render/ImageLoader.h>

namespace MeteorEngine
{

	class METEOR_API ImageCore
	{
	public:
		ImageCore();
		~ImageCore();
		bool Load(const std::string&);
		Vector2u GetSize() const { return m_size; }

		s32 GetChannels() const { return m_channels; }
		const u8* GetPointer() const { if (!m_pointer.empty()) return m_pointer.data(); else return NULL; }

		void FlipX();
		void FlipY();
	private:
		Vector2u			m_size;
		std::vector<u8>		m_pointer;
		s32					m_channels;
	};
}
#endif // !IMAGECORE_H
