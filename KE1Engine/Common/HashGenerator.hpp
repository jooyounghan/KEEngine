#include "HashGenerator.h"
#include "TypeTraits.h"
#include "TemplateCommon.h"

namespace ke
{
#if SIZE_MAX == UINT64_MAX
    using hash_t = uint64_t;
    constexpr hash_t PRIME_1 = 0x9E3779B185EBCA87ULL;
    constexpr hash_t PRIME_2 = 0xC2B2AE3D27D4EB4FULL;
    constexpr hash_t PRIME_3 = 0x165667B19E3779F9ULL;
    constexpr hash_t PRIME_4 = 0x85EBCA77C2B2AE63ULL;
    constexpr hash_t SEED_1 = 0x0123456789ABCDEFULL;
    constexpr hash_t SEED_2 = 0xFEDCBA9876543210ULL;
    constexpr size_t SECRET_SIZE = 32;
#else
    using hash_t = uint32_t;
    constexpr hash_t PRIME_1 = 0x9E3779B1U;
    constexpr hash_t PRIME_2 = 0x85EBCA77U;
    constexpr hash_t PRIME_3 = 0x27D4EB2FU;
    constexpr hash_t PRIME_4 = 0x165667B1U;
    constexpr hash_t SEED_1 = 0x1234567U;
    constexpr hash_t SEED_2 = 0x89ABCDEFU;
    constexpr size_t SECRET_SIZE = 16;
#endif

    constexpr uint8_t DEFAULT_SECRET[SECRET_SIZE] = {
        0xb8, 0xfe, 0x6c, 0x39, 0x23, 0xa4, 0x4b, 0xbe,
        0x1d, 0xf2, 0xe6, 0x19, 0x31, 0x48, 0x3f, 0xc1,
#if SIZE_MAX == UINT64_MAX
        0x96, 0x69, 0x12, 0x6e, 0xe8, 0x93, 0xd1, 0x2e,
        0x89, 0xde, 0xcb, 0x0c, 0xf7, 0x1e, 0x4b, 0xf6
#endif
    };

    template<typename T>
    size_t HashGenerator<T>::operator()(const T& value)
    {
        return convertToHash(value);
    }

    template<typename T>
    size_t HashGenerator<T>::computeHash(const void* data, size_t len)
    {
        const uint8_t* input = reinterpret_cast<const uint8_t*>(data);

        hash_t acc1 = SEED_1 + PRIME_1 + PRIME_2;
        hash_t acc2 = SEED_2 + PRIME_2;

        size_t i = 0;
        while (i + sizeof(hash_t) <= len)
        {
            hash_t lane;
            std::memcpy(&lane, input + i, sizeof(hash_t));
            hash_t secret_lane;
            std::memcpy(&secret_lane, DEFAULT_SECRET + (i % (SECRET_SIZE - sizeof(hash_t) + 1)), sizeof(hash_t));

            hash_t mixed = lane ^ secret_lane;

            acc1 += mixed * PRIME_1;
            acc1 = (acc1 << 13) | (acc1 >> (sizeof(hash_t) * 8 - 13));
            acc1 *= PRIME_2;

            acc2 ^= mixed;
            acc2 *= PRIME_3;
            acc2 = (acc2 << 11) | (acc2 >> (sizeof(hash_t) * 8 - 11));
            acc2 *= PRIME_4;

            i += sizeof(hash_t);
        }

        for (; i < len; ++i)
        {
            acc1 ^= input[i];
            acc1 *= PRIME_1;
        }

        size_t result = static_cast<size_t>(acc1 ^ acc2);
        return result;
    }

    template<typename T>
    size_t HashGenerator<T>::convertToHash(const T& value)
    {
        STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(HashGenerator);
    }

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
}

