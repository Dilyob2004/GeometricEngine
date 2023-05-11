#ifndef FILE_H
#define FILE_H
#include <Engine/Core/Config.h>
#include <Engine/Core/Generic/FileBase.h>
#include <Engine/Core/Misc/String.h>

namespace GeometricEngine
{
	class GEOMETRIC_API File
	{
	public:
		File() = default;
		~File() = default;
		static File* Create(const String&, FileMode, FileAccess, FileShare);

		virtual bool Read(void*, U32, U32*) = 0;
		virtual bool Write(const void*, U32, U32*) = 0;
		virtual void Close() = 0;
		virtual bool IsOpen() = 0;
		virtual void Seek(U32) = 0;



		virtual U32 GetSize() const = 0;
		virtual U32 GetSeek() const = 0;

	};
}
#endif // !FILE_H
