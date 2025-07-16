#pragma once
#include "TypeCommon.h"
#include "Hash128.h"

namespace ke
{
    class HashConvertor
    {
    private:
        static Hash128 computeFNV1a128(const void* data, uint64 len);

    public:
        template<typename T>
        static Hash128 convertToHash(const T& value);
        static Hash128 convertToHash(const char* cstr);
    };
}

#include "HashConvertor.hpp"