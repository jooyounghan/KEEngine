#pragma once
#include <intrin.h>
#include <immintrin.h>

namespace ke
{
#if defined(__AVX512F__)
#define SIMD_ENABLED          1
#define SIMD_TARGET_BYTE      64
#define SIMD_VEC              __m512i

#define SIMD_SET1_EPI8(x)     _mm512_set1_epi8(x)
#define SIMD_LOAD(p)          _mm512_loadu_si512(reinterpret_cast<const __m512i*>(p))
#define SIMD_CMP_EPI8(a,b)    _mm512_cmpeq_epi8_mask(a,b)
#define SIMD_MASK_TYPE        unsigned long long
#define SIMD_ALL_ONES_MASK    (0xFFFFFFFFFFFFFFFFULL)

#if defined(_MSC_VER)
#define SIMD_MASK_BSF(idx, mask)  _BitScanForward64(&(idx), (mask))
#else
#define SIMD_MASK_BSF(idx, mask)  (idx = __builtin_ctzll(mask))
#endif

#elif defined(__AVX2__)
#define SIMD_ENABLED          1
#define SIMD_TARGET_BYTE      32
#define SIMD_VEC              __m256i

#define SIMD_SET1_EPI8(x)     _mm256_set1_epi8(x)
#define SIMD_LOAD(p)          _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p))
#define SIMD_CMP_EPI8(a,b)    _mm256_movemask_epi8(_mm256_cmpeq_epi8(a,b))
#define SIMD_MASK_TYPE        unsigned int
#define SIMD_ALL_ONES_MASK    (0xFFFFFFFFu)

#if defined(_MSC_VER)
#define SIMD_MASK_BSF(idx, mask)  _BitScanForward(&(idx), (mask))
#else
#define SIMD_MASK_BSF(idx, mask)  (idx = __builtin_ctz(mask))
#endif

#else
#define SIMD_ENABLED          0
#define SIMD_TARGET_BYTE      0
#endif
}