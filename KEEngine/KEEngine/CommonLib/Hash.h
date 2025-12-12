#pragma once
#include "CommonLibPch.h"

// This hash function is inspired by xxHash, but implemented independently.
// It does not use any code from the official xxHash project.
#define DECLARE_RAW_VALUE_HASH_SPECIALIZATION(Raw) template<> size_t Hash<Raw>::convertToHash(const Raw& value);
#define DECLARE_TEMPLATED_HASH_SPECIALIZATION(Class, ...) template<> size_t Hash<Class<__VA_ARGS__>>::convertToHash(const Class<__VA_ARGS__>& value);

#define USE_MANUAL_HASH true

#if USE_MANUAL_HASH
    #define HASH(T) ke::Hash<T>
#else
    #define HASH(T) std::hash<T>
#endif // DEBUG



namespace ke
{
    template<typename T>
    class Hash
    {
    public:
        NODISC static size_t operator()(const T& value);

    private:
        static size_t computeHash(const void* data, size_t len);

    private:
        static size_t convertToHash(const T& value);
    };

    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(bool);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(uint64);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(uint32);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(uint16);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(uint8);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(int64);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(int32);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(int16);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(int8);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(double);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(float);

    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(std::basic_string_view<char>);
    DECLARE_RAW_VALUE_HASH_SPECIALIZATION(std::basic_string_view<wchar_t>);
}

#include "Hash.hpp"