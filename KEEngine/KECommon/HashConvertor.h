#pragma once
#include "TypeCommon.h"
#include "Hash128.h"

// This hash function is inspired by xxHash, but implemented independently.
// It does not use any code from the official xxHash project.

namespace ke
{
    class HashConvertor
    {
    private:
        static Hash128 computeHash(const void* data, uint64 len);
        static Hash128 computeSimdHashAVX2(const uint8_t* input, size_t len);
        static Hash128 computeSimdHashSSE2(const uint8_t* input, size_t len);
        static Hash128 computeScalarHash(const uint8_t* input, size_t len);

    public:
        template<typename T>
        static Hash128 convertToHash(const T& value);
        static Hash128 convertToHash(const char* cstr);
    };
}

#include "HashConvertor.hpp"