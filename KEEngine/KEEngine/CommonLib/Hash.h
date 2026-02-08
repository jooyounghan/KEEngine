#pragma once

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
        NODISC size_t operator()(const T& value) const;

    private:
        static size_t computeHash(const void* data, size_t len);

    private:
        static size_t convertToHash(const T& value);
    };
}

#include "Hash.hpp"