#include "HashConvertor.h"
#include <immintrin.h>

namespace ke
{
    constexpr uint64 FNV_OFFSET_LOW = 0x62b821756295c58dULL;
    constexpr uint64 FNV_OFFSET_HIGH = 0x6c62272e07bb0142ULL;
    constexpr uint64 FNV_PRIME_64 = 1099511628211ULL;

    Hash128 HashConvertor::computeFNV1a128(const void* data, uint64 len)
    {
        const uint8_t* ptr = reinterpret_cast<const uint8_t*>(data);
        Hash128 hash = { FNV_OFFSET_LOW, FNV_OFFSET_HIGH };

#if defined(__AVX2__)
        constexpr std::size_t blockSize = 32;
        std::size_t i = 0;
        for (; i + blockSize <= len; i += blockSize) 
        {
            __m256i block = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr + i));
            alignas(32) uint8_t buffer[blockSize];
            _mm256_store_si256(reinterpret_cast<__m256i*>(buffer), block);

            for (int j = 0; j < blockSize; ++j) 
            {
                hash ^= buffer[j];
                hash *= FNV_PRIME_64;
            }
        }
        ptr += i;
        len -= i;

#elif defined(__SSE2__)
        constexpr std::size_t blockSize = 16;
        std::size_t i = 0;
        for (; i + blockSize <= len; i += blockSize) 
        {
            __m128i block = _mm_loadu_si128(reinterpret_cast<const __m128i*>(ptr + i));
            alignas(16) uint8_t buffer[blockSize];
            _mm_store_si128(reinterpret_cast<__m128i*>(buffer), block);

            for (int j = 0; j < blockSize; ++j) 
            {
                hash ^= buffer[j];
                hash *= FNV_PRIME_64;
            }
        }
        ptr += i;
        len -= i;
#endif
        for (std::size_t idx = 0; idx < len; ++idx) {
            hash ^= ptr[idx];
            hash *= FNV_PRIME_64;
        }

        return hash;
    }

    Hash128 HashConvertor::convertToHash(const char* cstr)
    {
        return computeFNV1a128(cstr, strlen(cstr));
    }
}

