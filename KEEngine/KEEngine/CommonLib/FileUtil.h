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
		
		// Calculate the total size needed to merge files (without reading file contents)
		// Returns 0 if any file is invalid
		static size_t getMergeSize(
			const FileMergeInfo* files,
			size_t count
		);
		
		// Merge files into the output buffer
		// Caller should ensure buffer has sufficient capacity (use getMergeSize first)
		static bool mergeFiles(
			const FileMergeInfo* files,
			size_t count,
			IBuffer* outputBuffer
		);
	};
}
