#include <Engine/Core/Windows/WindowsFile.h>

#include <Engine/Core/Misc/Log.h>

namespace GeometricEngine
{

	WindowsFile::WindowsFile(void* pHandle) :
		Handle(pHandle)
	{
	}
	WindowsFile* WindowsFile::Open(const String& Path, FileMode Mode, FileAccess Access, FileShare Share)
	{

		DWORD DWAccess = 0, DWShare = 0, DWMode = 0;
		if (Access == FileAccess::Read)		DWAccess |= GENERIC_READ;
		if (Access == FileAccess::Write)	DWAccess |= GENERIC_WRITE;

		if (Share == FileShare::Read)		DWShare |= FILE_SHARE_READ;
		if (Share == FileShare::Write)		DWShare |= FILE_SHARE_WRITE;
		if (Share == FileShare::Delete)		DWShare |= FILE_SHARE_DELETE;

		if (Mode == FileMode::CreateAlways)		DWMode |= CREATE_ALWAYS;
		if (Mode == FileMode::CreateNew)		DWMode |= CREATE_NEW;
		if (Mode == FileMode::OpenAlways)		DWMode |= OPEN_ALWAYS;
		if (Mode == FileMode::OpenExisting)		DWMode |= OPEN_EXISTING;
		if (Mode == FileMode::TruncateExisting) DWMode |= TRUNCATE_EXISTING;

		HANDLE DummyHandle = CreateFileA(Path.Pointer(), DWAccess, DWShare, NULL, DWMode, FILE_ATTRIBUTE_NORMAL, NULL);

		if (DummyHandle == INVALID_HANDLE_VALUE) 
			return NULL;
		

		return new WindowsFile(DummyHandle);
	}
	bool WindowsFile::Read(void* Buffer , U32 Size, U32* OutSize)
	{
		DWORD temp = 0;
		if (ReadFile(Handle, Buffer, Size, &temp, NULL))
		{
			if (OutSize)
				 * OutSize = temp;
			return true;
		}

		if (OutSize)
			* OutSize = 0;
		return false;
	}
	bool WindowsFile::Write(const void* Buffer, U32 Size, U32* OutSize)
	{
		DWORD temp;
		if (WriteFile(Handle, Buffer, Size, &temp, NULL))
		{
			if (OutSize)
				* OutSize = temp;
			return true;
		}

		if (OutSize)
			* OutSize = 0;
		return false;

	}
	void WindowsFile::Close()
	{ 
		if (Handle)
		{
			CloseHandle(Handle);
			Handle = NULL;
		}
	}
	bool WindowsFile::IsOpen()
	{ 
		return Handle != NULL;
	}
	void WindowsFile::Seek(U32 Seek)
	{
		SetFilePointer(Handle, Seek, NULL, FILE_BEGIN);
	}

	U32 WindowsFile::GetSize() const
	{
		LARGE_INTEGER result;
		GetFileSizeEx(Handle, &result);
		return (U32)result.QuadPart;
	}
	U32 WindowsFile::GetSeek() const
	{
		return SetFilePointer(Handle, 0, NULL, FILE_CURRENT);
	}
}