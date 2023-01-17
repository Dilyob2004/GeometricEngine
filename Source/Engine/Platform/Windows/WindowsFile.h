#ifndef WINDOWSFILE_H
#define WINDOWSFILE_H
#include <Engine/Core/Config.h>
#include <Engine/System/File.h>

namespace MeteorEngine
{
	class METEOR_API WindowsFile : public File
	{
	public:
		WindowsFile() = default;
		WindowsFile(void* handle);
		~WindowsFile() = default;

		static WindowsFile* Open(const std::string&, FileMode, FileAccess, FileShare);
		virtual bool Read(void*, u32, u32*) override;
		virtual bool Write(const void*, u32, u32*)override;
		virtual void Close() override;
		virtual bool IsOpen() override;
		virtual void Seek(u32) override;


		virtual u32 GetSize() const override;
		virtual u32 GetSeek() const override;


	private:
		void* m_handle = NULL;

	};
}
#endif // !WINDOWSFILE_H
