#ifndef WINDOWSFILE_H
#define WINDOWSFILE_H
#include <Engine/Core/Config.h>
#include <Engine/Core/Generic/File.h>

namespace GeometricEngine
{
	class METEOR_API WindowsFile : public File
	{
	public:
		WindowsFile() = default;
		WindowsFile(void* handle);
		~WindowsFile() = default;

		static WindowsFile* Open(const std::string&, FileMode, FileAccess, FileShare);
		virtual bool Read(void*, U32, U32*) override;
		virtual bool Write(const void*, U32, U32*)override;
		virtual void Close() override;
		virtual bool IsOpen() override;
		virtual void Seek(U32) override;


		virtual U32 GetSize() const override;
		virtual U32 GetSeek() const override;


	private:
		void* m_handle = NULL;

	};
}
#endif // !WINDOWSFILE_H
