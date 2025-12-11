#include "CommonLibPch.h"
#include "File.h"

#define VALIDATE_FILE_CORE() {                                      \
	KE_DEBUG_ASSERT(_fileCore != nullptr, "FileCore is null.");     \
    if (_fileCore == nullptr) return;                               \
    FILE* fp = _fileCore->getFilePointer();                         \
	KE_DEBUG_ASSERT(fp != nullptr, "File Pointer is null."); }

namespace ke
{
    DEFINE_ENUM_DESCRIPTOR(EOpenMode,
        rb,
        wb,
        r + b
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

    uint64 FileCore::getFileSize() const
    {
        if (_fp == nullptr) return 0;

        long long cur = _ftelli64(_fp);
        _fseeki64(_fp, 0, SEEK_END);
        uint64 size = static_cast<uint64>(_ftelli64(_fp));
        _fseeki64(_fp, cur, SEEK_SET);
        return size;
    }

    FileCore::FileCore(const char* path, EOpenMode openMode)
    {
        _openStatus = FileCore::openFile(path, GET_ENUM_STRING(EOpenMode, openMode), _fp);
        if (_openStatus == 0) _fileSize = getFileSize();
    }

    FileCore::~FileCore()
    {
        if (_fp != nullptr)
        {
            fclose(_fp);
            _fp = nullptr;
        }
    }

    AllowRead::AllowRead(FileCore& fileCore)
        : _fileCore(&fileCore)
    {

    }

    void AllowRead::read(IBuffer* buffer, size_t size)
    {
        VALIDATE_FILE_CORE();

        FILE* fp = _fileCore->getFilePointer();
        if (buffer != nullptr && fseek(fp, 0, SEEK_CUR) == 0)
        {
            size_t bytesRead = fread(buffer, 1, size, fp);
            if (bytesRead != size || ferror(fp))
            {
                KE_DEBUG_ASSERT(false, "File read error occurred.");
            }
            else
            {
                updateOffset(ftell(fp));
            }
        }
    }

    void AllowRead::setOffset(size_t offset)
    {
        VALIDATE_FILE_CORE();
        FILE* fp = _fileCore->getFilePointer();
        if (fseek(fp, static_cast<long>(offset), SEEK_SET) == 0)
        {
            updateOffset(ftell(fp));
        }
    }

    void AllowRead::updateOffset(long ftellResult)
    {
        if (ftellResult != -1)
        {
            _fileOffset = static_cast<size_t>(ftellResult);
            return;
        }

        KE_DEBUG_ASSERT(false, "Failed to get current file position.");
    }

    AllowWrite::AllowWrite(FileCore& fileCore)
        : _fileCore(&fileCore)
    {
    }

    void AllowWrite::write(const IBuffer* buffer, size_t count)
    {
        VALIDATE_FILE_CORE();
        FILE* fp = _fileCore->getFilePointer();
        if (count < buffer->getCursorPos())
        {
            fwrite(buffer->getConstBuffer(), 1, count, fp);
        }
    }

    template class File<BlockRead, BlockWrite, EOpenMode::ReadOnly>;
    template class File<BlockRead, BlockWrite, EOpenMode::WriteOnly>;
    template class File<BlockRead, BlockWrite, EOpenMode::ReadWrite>;

    template class File<BlockRead, AllowWrite, EOpenMode::ReadOnly>;
    template class File<BlockRead, AllowWrite, EOpenMode::WriteOnly>;
    template class File<BlockRead, AllowWrite, EOpenMode::ReadWrite>;

    template class File<AllowRead, BlockWrite, EOpenMode::ReadOnly>;
    template class File<AllowRead, BlockWrite, EOpenMode::WriteOnly>;
    template class File<AllowRead, BlockWrite, EOpenMode::ReadWrite>;

    template class File<AllowRead, AllowWrite, EOpenMode::ReadOnly>;
    template class File<AllowRead, AllowWrite, EOpenMode::WriteOnly>;
    template class File<AllowRead, AllowWrite, EOpenMode::ReadWrite>;
}
