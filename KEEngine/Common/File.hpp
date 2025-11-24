#pragma once
#include "File.h"

namespace ke
{
    template<size_t BufferSize>
    AllowWrite<BufferSize>::AllowWrite(FileCore& fileCore)
        : _fileCore(&fileCore)
    {
    }

    template<size_t BufferSize>
    AllowWrite<BufferSize>::~AllowWrite()
    {
        flush();
    }

    template<size_t BufferSize>
    void AllowWrite<BufferSize>::write(const void* const input, size_t count)
    {
        VALIDATE_FILE_CORE();

        FILE* fp = _fileCore->getFilePointer();
        if (fp == nullptr || BufferSize < count)
        {
            KE_DEBUG_ASSERT(false, "File write error: invalid file pointer or write size exceeds buffer size.");
            return;
        }

        if (count + _writeBuffer.getCount() > KEConstant::kFileWriteBufferSize)
        {
            flush();
        }

        _writeBuffer.write(input, count);
    }

    template<size_t BufferSize>
    void AllowWrite<BufferSize>::flush()
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