#include <Engine/Core/Windows/WindowsFileSystem.h> 
#include <Engine/Core/Misc/Log.h>

namespace GeometricEngine
{
	static WIN32_FIND_DATAA    m_findData = WIN32_FIND_DATAA();
	static HANDLE              m_hFind = (HANDLE)-1;



	void WindowsFileSystem::Open(const Path& pathFile)
	{
		m_hFind = FindFirstFileA(pathFile.m_path.c_str(), &m_findData);
		if (m_hFind == (HANDLE)-1)
			LOG("Invalid handle value! Please check your path...\n");
	}
	bool WindowsFileSystem::CreateDirectoryIn(const std::string& path)
	{
		return ::CreateDirectoryA(path.c_str(), NULL);
	}
	bool WindowsFileSystem::MoveFileTo(const std::string& bufferDst, const std::string& bufferSrc, bool overwrite)
	{
		const DWORD flags = MOVEFILE_COPY_ALLOWED | (overwrite ? MOVEFILE_REPLACE_EXISTING : 0);
		return ::MoveFileExA(bufferSrc.c_str(), bufferDst.c_str(), flags);
	}
	bool WindowsFileSystem::DeleteDirectory(const std::string& path)
	{
		return ::RemoveDirectoryA(path.c_str());
	}
	bool WindowsFileSystem::RemoveFile(const std::string& path)
	{
		return ::DeleteFileA(path.c_str());

	}
	void WindowsFileSystem::Close()
	{
		FindClose(m_hFind);
	}
	std::vector<Path> WindowsFileSystem::FindDirectory(Path path)
	{
		std::vector<Path> vPath;
		while (FindNextFileA(m_hFind, &m_findData) != 0)
		{
			path.fileName = std::string(m_findData.cFileName);
			path.isDirectory = m_findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
			vPath.push_back(path);
		}


		return vPath;
	}
}

