#include "File.h"
#include "MemoryCommon.h"

namespace ke
{
    errno_t File::openFile(FILE** out, const char* path, const char* mode)
    {
#ifdef _MSC_VER
        return fopen_s(out, path, mode);
#else
        FILE*& fp = *out;
        fp = fopen(path, mode);
        if (fp == nullptr)
        {
            return errno;
        }
        return 0;
#endif
    }

    File::File(const char* path)
    {
        FILE* fp = nullptr;
        errno_t openStatus = File::openFile(&fp, path, "rb");
        
        if (openStatus == 0)
        {
            fseek(fp, 0, SEEK_END);
			_size = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            _data = KEMemory::aligendMalloc<false, char>(_size + 1);

            if (_data != nullptr)
            {
                fread(_data, 1, _size, fp);
                static_cast<char*>(_data)[_size] = '\0';
			}

            fclose(fp);
        }
    }

    File::~File()
    {
        if (_data != nullptr)
        {
            KEMemory::aligendFree(_data);
        }
        _data = nullptr;
        _size = 0;
    }

}
