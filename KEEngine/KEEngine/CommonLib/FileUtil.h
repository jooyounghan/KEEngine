#pragma once

namespace ke
{
	class IBuffer;

	struct FileMergeInfo
	{
		const char* fileName;
		const char* preAdditional;
		const char* postAdditional;
	};

	struct FileUtil
	{
		static bool directoryExists(const char* path, bool createIfNotExist = false);
		static void collectFiles(
			const char* directoryPath,
			std::vector<std::string>& outFiles,
			const std::vector<std::string>& extensions = {},
			bool recursive = false
		);
		static int64_t getLastModifiedTime(const char* filePath);
		static bool mergeFiles(
			const FileMergeInfo* files,
			size_t count,
			IBuffer* outputBuffer
		);
	};
}
