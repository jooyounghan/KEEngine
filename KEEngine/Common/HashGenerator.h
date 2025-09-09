#pragma once
#include "TypeCommon.h"

// This hash function is inspired by xxHash, but implemented independently.
// It does not use any code from the official xxHash project.

namespace ke
{
    template<typename T>
    class HashGenerator
    {
    public:
        NODISC static size_t operator()(const T& value);

    private:
        static size_t computeHash(const void* data, size_t len);

    private:
        static size_t convertToHash(const T& value);
        static size_t convertToHash(const char* cstr);
        static size_t convertToHash(const wchar_t* cstr);
    };
}

#include "HashGenerator.hpp"