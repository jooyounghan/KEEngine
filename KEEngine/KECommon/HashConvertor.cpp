#include "HashConvertor.h"

namespace ke
{
    constexpr uint64_t PRIME64_1 = 0x9E3779B185EBCA87ULL;
    constexpr uint64_t PRIME64_2 = 0xC2B2AE3D27D4EB4FULL;
    constexpr uint64_t PRIME64_3 = 0x165667B19E3779F9ULL;
    constexpr uint64_t PRIME64_4 = 0x85EBCA77C2B2AE63ULL;
    constexpr uint64_t PRIME64_5 = 0x27D4EB2F165667C5ULL;

    constexpr uint64_t SEED_LOW = 0x0123456789ABCDEFULL;
    constexpr uint64_t SEED_HIGH = 0xFEDCBA9876543210ULL;

    static const uint8_t DEFAULT_SECRET[32] = {
        0xb8, 0xfe, 0x6c, 0x39, 0x23, 0xa4, 0x4b, 0xbe,
        0x1d, 0xf2, 0xe6, 0x19, 0x31, 0x48, 0x3f, 0xc1,
        0x96, 0x69, 0x12, 0x6e, 0xe8, 0x93, 0xd1, 0x2e,
        0x89, 0xde, 0xcb, 0x0c, 0xf7, 0x1e, 0x4b, 0xf6
    };

    Hash128 HashConvertor::computeHash(const void* data, uint64 len) 
    {
        const uint8_t* input = reinterpret_cast<const uint8_t*>(data);

#ifdef __AVX2__
        Hash128 hash = computeSimdHashAVX2(input, len);
        size_t processed = (len / 32) * 32;
#elif defined(__SSE2__)
        Hash128 hash = computeSimdHashSSE2(input, len);
        size_t processed = (len / 16) * 16;
#else
        Hash128 hash = computeScalarHash(input, len);
        size_t processed = (len / 8) * 8;
#endif

        uint64 low = hash._low;
        uint64 high = hash._high;

        for (size_t i = processed; i < len; ++i) {
            uint8_t byte = input[i];
            low ^= byte;
            low *= PRIME64_1;
            high ^= (byte + 0xA5);
            high *= PRIME64_2;
        }

        return Hash128(low, high);
    }

    Hash128 HashConvertor::computeSimdHashAVX2(const uint8_t* input, size_t len)
    {
        uint64 acc1 = SEED_LOW + PRIME64_1 + PRIME64_2;
        uint64 acc2 = SEED_HIGH + PRIME64_2;

        __m256i accA = _mm256_set1_epi64x(acc1);
        __m256i accB = _mm256_set1_epi64x(acc2);
        const __m256i prime1 = _mm256_set1_epi64x(PRIME64_1);
        const __m256i prime2 = _mm256_set1_epi64x(PRIME64_2);

        size_t i = 0;
        while (i + 64 <= len) {
            __m256i v1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(input + i));
            __m256i v2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(input + i + 32));
            __m256i secret1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(DEFAULT_SECRET));
            __m256i secret2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(DEFAULT_SECRET + 16));

            __m256i mixed1 = _mm256_xor_si256(v1, secret1);
            __m256i mixed2 = _mm256_xor_si256(v2, secret2);

            __m128i lo1 = _mm256_castsi256_si128(mixed1);
            __m128i hi1 = _mm256_extracti128_si256(mixed1, 1);
            __m128i lo2 = _mm256_castsi256_si128(mixed2);
            __m128i hi2 = _mm256_extracti128_si256(mixed2, 1);

            __m128i prod_lo1 = _mm_mul_epu32(lo1, _mm256_castsi256_si128(prime1));
            __m128i prod_hi1 = _mm_mul_epu32(hi1, _mm256_extracti128_si256(prime1, 1));
            __m128i prod_lo2 = _mm_mul_epu32(lo2, _mm256_castsi256_si128(prime1));
            __m128i prod_hi2 = _mm_mul_epu32(hi2, _mm256_extracti128_si256(prime1, 1));

            accA = _mm256_add_epi64(accA, _mm256_set_m128i(prod_hi1, prod_lo1));
            accB = _mm256_add_epi64(accB, _mm256_set_m128i(prod_hi2, prod_lo2));

            accA = _mm256_mul_epu32(accA, prime2);
            accB = _mm256_mul_epu32(accB, prime2);

            i += 64;
        }

        uint64 tempA[4], tempB[4];
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(tempA), accA);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(tempB), accB);

        uint64 low = tempA[0] ^ tempA[1] ^ tempA[2] ^ tempA[3];
        uint64 high = tempB[0] ^ tempB[1] ^ tempB[2] ^ tempB[3];

        return Hash128(low, high);
    }

    Hash128 HashConvertor::computeSimdHashSSE2(const uint8_t* input, size_t len)
    {
        uint64 acc1 = SEED_LOW + PRIME64_1 + PRIME64_2;
        uint64 acc2 = SEED_HIGH + PRIME64_2;

        __m128i acc = _mm_set_epi64x(acc2, acc1);
        const __m128i prime1 = _mm_set1_epi64x(PRIME64_1);
        const __m128i prime2 = _mm_set1_epi64x(PRIME64_2);

        size_t i = 0;
        while (i + 16 <= len) {
            __m128i dataVec = _mm_loadu_si128(reinterpret_cast<const __m128i*>(input + i));
            __m128i secretVec = _mm_loadu_si128(reinterpret_cast<const __m128i*>(DEFAULT_SECRET));
            __m128i mixed = _mm_xor_si128(dataVec, secretVec);
            __m128i product = _mm_mul_epu32(mixed, prime1);
            acc = _mm_add_epi64(acc, product);
            acc = _mm_mul_epu32(acc, prime2);
            i += 16;
        }

        uint64 temp[2];
        _mm_storeu_si128(reinterpret_cast<__m128i*>(temp), acc);
        return Hash128(temp[0], temp[1]);
    }

    Hash128 HashConvertor::computeScalarHash(const uint8_t* input, size_t len)
    {
        uint64 acc1 = SEED_LOW + PRIME64_1 + PRIME64_2;
        uint64 acc2 = SEED_HIGH + PRIME64_2;

        size_t i = 0;
        while (i + 8 <= len) {
            uint64 lane;
            std::memcpy(&lane, input + i, 8);
            uint64 secret_lane;
            std::memcpy(&secret_lane, DEFAULT_SECRET + (i % 24), 8);
            uint64 mixed = lane ^ secret_lane;

            acc1 += mixed * PRIME64_1;
            acc1 = (acc1 << 31) | (acc1 >> (64 - 31));
            acc1 *= PRIME64_2;

            acc2 ^= mixed;
            acc2 *= PRIME64_3;
            acc2 = (acc2 << 27) | (acc2 >> (64 - 27));
            acc2 *= PRIME64_4;

            i += 8;
        }

        return Hash128(acc1, acc2);
    }

    Hash128 HashConvertor::convertToHash(const char* cstr)
    {
        return computeHash(cstr, strlen(cstr));
    }
}

