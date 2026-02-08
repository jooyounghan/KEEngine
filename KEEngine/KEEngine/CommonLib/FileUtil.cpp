#include "CommonLibPch.h"
#include "FileUtil.h"

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#else
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <dirent.h>
	#include <cstring>
#endif

namespace ke
{
	// ---------------------------------------------------------------
	// Internal helpers
	// ---------------------------------------------------------------

	static bool createDirectoryRecursive(const char* path)
	{
		std::string fullPath(path);

		// Normalise separators to '/'
		for (char& c : fullPath)
		{
			if (c == '\\') c = '/';
		}

		// Iterate through the path and create each directory level
		for (size_t i = 1; i < fullPath.size(); ++i)
		{
			if (fullPath[i] == '/')
			{
				fullPath[i] = '\0';

#ifdef _WIN32
				CreateDirectoryA(fullPath.c_str(), nullptr);
#else
				mkdir(fullPath.c_str(), 0755);
#endif
				fullPath[i] = '/';
			}
		}

		// Create the final directory
#ifdef _WIN32
		CreateDirectoryA(fullPath.c_str(), nullptr);
#else
		mkdir(fullPath.c_str(), 0755);
#endif

		// Verify it was created
#ifdef _WIN32
		DWORD attr = GetFileAttributesA(fullPath.c_str());
		return (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY));
#else
		struct stat st;
		return (stat(fullPath.c_str(), &st) == 0 && S_ISDIR(st.st_mode));
#endif
	}

	static bool matchesExtension(const std::string& fileName, const std::vector<std::string>& extensions)
	{
		if (extensions.empty())
		{
			return true;
		}

		for (const auto& ext : extensions)
		{
			if (fileName.size() >= ext.size())
			{
				size_t offset = fileName.size() - ext.size();
				if (fileName.compare(offset, ext.size(), ext) == 0)
				{
					return true;
				}
			}
		}

		return false;
	}

	static void collectFilesInternal(
		const char* directoryPath,
		std::vector<std::string>& outFiles,
		const std::vector<std::string>& extensions,
		bool recursive
	)
	{
#ifdef _WIN32
		std::string searchPath = std::string(directoryPath) + "\\*";
		WIN32_FIND_DATAA findData;
		HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

		if (hFind == INVALID_HANDLE_VALUE)
		{
			return;
		}

		do
		{
			const char* name = findData.cFileName;

			if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
			{
				continue;
			}

			std::string fullPath = std::string(directoryPath) + "\\" + name;

			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (recursive)
				{
					collectFilesInternal(fullPath.c_str(), outFiles, extensions, recursive);
				}
			}
			else
			{
				if (matchesExtension(name, extensions))
				{
					outFiles.push_back(fullPath);
				}
			}
		} while (FindNextFileA(hFind, &findData));

		FindClose(hFind);
#else
		DIR* dir = opendir(directoryPath);
		if (!dir)
		{
			return;
		}

		struct dirent* entry;
		while ((entry = readdir(dir)) != nullptr)
		{
			const char* name = entry->d_name;

			if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
			{
				continue;
			}

			std::string fullPath = std::string(directoryPath) + "/" + name;

			struct stat st;
			if (stat(fullPath.c_str(), &st) != 0)
			{
				continue;
			}

			if (S_ISDIR(st.st_mode))
			{
				if (recursive)
				{
					collectFilesInternal(fullPath.c_str(), outFiles, extensions, recursive);
				}
			}
			else if (S_ISREG(st.st_mode))
			{
				if (matchesExtension(name, extensions))
				{
					outFiles.push_back(fullPath);
				}
			}
		}

		closedir(dir);
#endif
	}

	// ---------------------------------------------------------------
	// FileUtil public interface
	// ---------------------------------------------------------------

	bool FileUtil::directoryExists(const char* path, bool createIfNotExist)
	{
#ifdef _WIN32
		DWORD attr = GetFileAttributesA(path);
		bool exists = (attr != INVALID_FILE_ATTRIBUTES && (attr & FILE_ATTRIBUTE_DIRECTORY));
#else
		struct stat st;
		bool exists = (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
#endif

		if (exists)
		{
			return true;
		}

		if (createIfNotExist)
		{
			return createDirectoryRecursive(path);
		}

		return false;
	}

	void FileUtil::collectFiles(
		const char* directoryPath,
		std::vector<std::string>& outFiles,
		const std::vector<std::string>& extensions,
		bool recursive
	)
	{
		collectFilesInternal(directoryPath, outFiles, extensions, recursive);
	}

	void FileUtil::collectFiles(
		const char* directoryPath,
		std::vector<std::string>& outFiles,
		const std::vector<const char*>& extensions,
		bool recursive
	)
	{
		std::vector<std::string> exts;
		exts.reserve(extensions.size());
		for (const char* ext : extensions)
		{
			exts.emplace_back(ext);
		}
		collectFilesInternal(directoryPath, outFiles, exts, recursive);
	}

	int64_t FileUtil::getLastModifiedTime(const char* filePath)
	{
#ifdef _WIN32
		WIN32_FILE_ATTRIBUTE_DATA fileInfo;
		if (!GetFileAttributesExA(filePath, GetFileExInfoStandard, &fileInfo))
		{
			return -1;
		}

		// Convert FILETIME to int64 (100-nanosecond intervals since 1601-01-01)
		ULARGE_INTEGER ull;
		ull.LowPart = fileInfo.ftLastWriteTime.dwLowDateTime;
		ull.HighPart = fileInfo.ftLastWriteTime.dwHighDateTime;

		// Convert to Unix epoch seconds (subtract Windows-to-Unix epoch offset)
		constexpr int64_t epochDiff = 116444736000000000LL;
		return static_cast<int64_t>((ull.QuadPart - epochDiff) / 10000000LL);
#else
		struct stat st;
		if (stat(filePath, &st) != 0)
		{
			return -1;
		}
		return static_cast<int64_t>(st.st_mtime);
#endif
	}
}
