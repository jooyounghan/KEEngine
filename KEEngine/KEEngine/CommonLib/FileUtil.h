#pragma once

namespace ke
{
	struct FileUtil
	{
		// Checks whether the directory at 'path' exists.
		// If 'createIfNotExist' is true and the directory does not exist,
		// creates the full directory hierarchy and returns true.
		static bool directoryExists(const char* path, bool createIfNotExist = false);

		// Collects file names (full paths) under 'directoryPath' into 'outFiles'.
		// 'extensions' filters by extension (e.g. ".png", ".txt"). Empty means all files.
		// 'recursive' controls whether subdirectories are traversed.
		static void collectFiles(
			const char* directoryPath,
			std::vector<std::string>& outFiles,
			const std::vector<std::string>& extensions = {},
			bool recursive = false
		);

		// Overload accepting const char* extensions for convenience.
		static void collectFiles(
			const char* directoryPath,
			std::vector<std::string>& outFiles,
			const std::vector<const char*>& extensions,
			bool recursive = false
		);

		// Returns the last modification time of the file at 'filePath'
		// as a Unix-epoch timestamp in seconds (int64_t).
		// Returns -1 on failure.
		static int64_t getLastModifiedTime(const char* filePath);
	};
}
