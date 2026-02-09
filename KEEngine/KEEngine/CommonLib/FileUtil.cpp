#include "CommonLibPch.h"
#include "FileUtil.h"

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

	bool FileUtil::mergeFiles(
		const FileMergeInfo* files,
		size_t count,
		const char* outputPath
	)
	{
		if (!files || count == 0 || !outputPath)
		{
			return false;
		}

		std::ofstream outFile(outputPath, std::ios::binary);
		if (!outFile.is_open())
		{
			return false;
		}

		// Reusable buffer for reading files
		constexpr size_t chunkSize = 65536; // 64KB chunks
		std::vector<char> buffer(chunkSize);

		for (size_t i = 0; i < count; ++i)
		{
			const FileMergeInfo& info = files[i];

			// Write preAdditional if provided
			if (info.preAdditional)
			{
				size_t preLen = strlen(info.preAdditional);
				outFile.write(info.preAdditional, preLen);
				if (!outFile.good())
				{
					outFile.close();
					return false;
				}
			}

			// Read and write file content if fileName is provided
			if (info.fileName)
			{
				std::ifstream inFile(info.fileName, std::ios::binary);
				if (!inFile.is_open())
				{
					outFile.close();
					return false;
				}

				// Get file size
				inFile.seekg(0, std::ios::end);
				if (!inFile.good())
				{
					inFile.close();
					outFile.close();
					return false;
				}

				std::streamsize fileSize = inFile.tellg();
				if (fileSize < 0)
				{
					inFile.close();
					outFile.close();
					return false;
				}

				inFile.seekg(0, std::ios::beg);
				if (!inFile.good())
				{
					inFile.close();
					outFile.close();
					return false;
				}

				// Read and write file content in chunks
				if (fileSize > 0)
				{
					std::streamsize remaining = fileSize;

					while (remaining > 0)
					{
						std::streamsize toRead = (remaining < static_cast<std::streamsize>(chunkSize)) 
							? remaining 
							: static_cast<std::streamsize>(chunkSize);

						inFile.read(buffer.data(), toRead);
						std::streamsize bytesRead = inFile.gcount();

						if (bytesRead != toRead)
						{
							inFile.close();
							outFile.close();
							return false;
						}

						outFile.write(buffer.data(), bytesRead);
						if (!outFile.good())
						{
							inFile.close();
							outFile.close();
							return false;
						}

						remaining -= bytesRead;
					}
				}
				inFile.close();
			}

			// Write postAdditional if provided
			if (info.postAdditional)
			{
				size_t postLen = strlen(info.postAdditional);
				outFile.write(info.postAdditional, postLen);
				if (!outFile.good())
				{
					outFile.close();
					return false;
				}
			}
		}

		outFile.close();
		return true;
	}
}
