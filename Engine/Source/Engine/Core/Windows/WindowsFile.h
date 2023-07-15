#ifndef WINDOWSFILE_H
#define WINDOWSFILE_H

#include <Engine/Core/Generic/File.h>
#include <Windows.h>

class GEOMETRIC_API WindowsFile : public File
{
public:

	static WindowsFile* Open(const String& , FileMode, FileAccess, FileShare);
	virtual bool Read(void*, U32, U32*);
	virtual bool Write(const void*, U32, U32*)override;
	virtual void Close() override;
	virtual bool IsOpen() override;
	virtual void Seek(U32) override;


	virtual U32 GetSize() const override;
	virtual U32 GetSeek() const override;


private:
	explicit WindowsFile(HANDLE);

	HANDLE Handle = NULL;

};

#endif // !WINDOWSFILE_H
