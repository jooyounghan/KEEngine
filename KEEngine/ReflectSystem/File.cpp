#include "File.h"
#include "MemoryCommon.h"

namespace ke
{
    DEFINE_ENUM_DESCRIPTOR(EOpenMode,
        rb,
        wb,
        r+b
	);

    errno_t FileCore::openFile(const char* path, const char* mode, FILE*& fpOut)
    {
#ifdef _MSC_VER
        return fopen_s(&fpOut, path, mode);
#else
        fpOut = fopen(path, mode);
        if (fpOut == nullptr)
        {
            return errno;
        }
        return 0;
#endif
    }

    FileCore::FileCore(const char* path, EOpenMode openMode)
    {
        _openStatus = FileCore::openFile(path, GET_ENUM_STRING(EOpenMode, openMode), _fp);
    }

    FileCore::~FileCore()
    {        
        if(_fp != nullptr)
        {
            fclose(_fp);
            _fp = nullptr;
		}
    }

#define VALIDATE_FILE_CORE() if (_fileCore == nullptr) return

    AllowRead::AllowRead(FileCore& fileCore)
        : _fileCore(&fileCore)
    {

    }
    void AllowRead::readAll()
    {
        VALIDATE_FILE_CORE();

		freeData();
        if (_fileCore->getOpenStatus() == 0)
        {
			FILE* fp = _fileCore->getFilePointer();
            fseek(fp, 0, SEEK_END);
            _size = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            _data = KEMemory::aligendMalloc<false, char>(_size + 1);

            if (_data != nullptr)
            {
                fread(_data, 1, _size, fp);
                static_cast<char*>(_data)[_size] = '\0';
            }
        }
    }

    void AllowRead::read(size_t offset, size_t size)
    {
        VALIDATE_FILE_CORE();

        freeData();

        FILE* fp = _fileCore->getFilePointer();
        if (fseek(fp, static_cast<long>(offset), SEEK_SET) == 0) 
        {
            void* readBuffer = KEMemory::aligendMalloc<false, char>(size + 1);
            
            size_t bytesRead = fread(readBuffer, 1, size, fp);
            if (bytesRead < size && ferror(fp)) 
            {
                KEMemory::aligendFree(readBuffer);
            }
            else
            {
				_data = readBuffer;
                _size = bytesRead;
            }
	    }
    }

    void AllowRead::freeData()
    {
        if (_data != nullptr)
        {
            KEMemory::aligendFree(_data);
        }
        _data = nullptr;
        _size = 0;
    }

    AllowWrite::AllowWrite(FileCore& fileCore)
        : _fileCore(&fileCore)
    {
    }

    AllowWrite::~AllowWrite()
    {
        flush();
	}

    void AllowWrite::write(const void* const input, size_t count)
    {
        VALIDATE_FILE_CORE();

        FILE* fp = _fileCore->getFilePointer();
        if (fp == nullptr || KEConstant::kFileWriteBufferSize < count)
        {
            return;
		}

        if (count + _writeBuffer.getCount() > KEConstant::kFileWriteBufferSize)
        {
            flush();
		}

		_writeBuffer.write(input, count);
	}

    void AllowWrite::flush()
    {
        VALIDATE_FILE_CORE();
        FILE* fp = _fileCore->getFilePointer();

        if (_writeBuffer.getCount() > 0 && fp != nullptr)
        {
            fwrite(_writeBuffer.getBuffer(), 1, _writeBuffer.getCount(), fp);
            _writeBuffer.reset();
        }
    }
}
