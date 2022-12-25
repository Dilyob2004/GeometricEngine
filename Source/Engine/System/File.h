#ifndef FILE_H
#define FILE_H
#include <Engine/Core/Config.h>
#include <Engine/System/FileBase.h>


namespace MeteorEngine
{
	class METEOR_API File
	{
	public:
		File() = default;
		~File() = default;
		static File* Create(const std::string&, FileMode, FileAccess, FileShare);

		virtual bool Read(void*, u32, u32*) = 0;
		virtual bool Write(const void*, u32, u32*) = 0;
		virtual void Close() = 0;
		virtual bool IsOpen() = 0;
		virtual void Seek(u32) = 0;



		virtual u32 GetSize() const = 0;
		virtual u32 GetSeek() const = 0;

	};
}
#endif // !FILE_H
