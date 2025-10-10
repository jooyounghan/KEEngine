#pragma once
#include "TypeCommon.h"

// This hash function is inspired by xxHash, but implemented independently.
// It does not use any code from the official xxHash project.
#define DECLARE_RAW_VALUE_HASH_SPECIALIZATION(Raw) template<> size_t HashGenerator<Raw>::convertToHash(const Raw& value);
#define DECLARE_TEMPLATED_HASH_SPECIALIZATION(Class, ...) template<> size_t HashGenerator<Class<__VA_ARGS__>>::convertToHash(const Class<__VA_ARGS__>& value);

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
    };
}

#include "HashGenerator.hpp"