#include <Engine/Platform/Win32/WindowsFile.h>


namespace MeteorEngine
{

	WindowsFile::WindowsFile(void* handle) :
		m_handle(handle)
	{
	}
	WindowsFile* WindowsFile::Open(const std::string& path, FileMode mode, FileAccess access, FileShare share)
	{
		auto handle = CreateFileA(path.c_str(), (DWORD)access, (DWORD)share, NULL, (DWORD)mode, FILE_ATTRIBUTE_NORMAL, NULL);

		if (handle == INVALID_HANDLE_VALUE)
			return NULL;

		return new WindowsFile(handle);
	}
	bool WindowsFile::Read(void* buffer , u32 bytesToRead, u32* bytesRead)
	{
		DWORD temp;
		if (ReadFile(m_handle, buffer, bytesToRead, &temp, NULL))
		{
			if (bytesRead)
				 *bytesRead = temp;
			return true;
		}

		if (bytesRead)
			* bytesRead = 0;
		return false;
	}
	bool WindowsFile::Write(const void* buffer, u32 bytesToRead, u32* bytesRead)
	{
		DWORD temp;
		if (WriteFile(m_handle, buffer, bytesToRead, &temp, NULL))
		{
			if (bytesRead)
				* bytesRead = temp;
			return true;
		}

		if (bytesRead)
			* bytesRead = 0;
		return false;

	}
	void WindowsFile::Close()
	{ 
		if (m_handle)
		{
			CloseHandle(m_handle);
			m_handle = NULL;
		}
	}
	bool WindowsFile::IsOpen()
	{ 
		return m_handle != NULL;
	}
	void WindowsFile::Seek(u32 seek)
	{
		SetFilePointer(m_handle, seek, NULL, FILE_BEGIN);
	}

	u32 WindowsFile::GetSize() const
	{

		LARGE_INTEGER result;
		GetFileSizeEx(m_handle, &result);
		return (u32)result.QuadPart;
	}
	u32 WindowsFile::GetSeek() const
	{
		return SetFilePointer(m_handle, 0, NULL, FILE_CURRENT);
	}
}