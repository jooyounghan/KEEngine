#pragma once
#include <cstdio>

namespace ke
{
	class File
	{
    public:
        File(const char* path);
		~File();

    private:
		void* _data = nullptr;
		long _size = 0;

	public:
		errno_t openFile(FILE** out, const char* path, const char* mode);

	public:
		inline bool isValid() const { return _data != nullptr; }
	};
}