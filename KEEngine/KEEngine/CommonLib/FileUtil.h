#pragma once

#if defined(__AVX512F__)
#define SIMD_WHITESPACE_MASK(chunk) CONVERT_TO_SIMD_MASK_TYPE(  \
        _mm512_cmpeq_epi8_mask(chunk, _mm512_set1_epi8(' '))  | \
        _mm512_cmpeq_epi8_mask(chunk, _mm512_set1_epi8('\t')) | \
        _mm512_cmpeq_epi8_mask(chunk, _mm512_set1_epi8('\n')) | \
        _mm512_cmpeq_epi8_mask(chunk, _mm512_set1_epi8('\r'))   \
    )
#elif defined(__AVX2__)
#define SIMD_WHITESPACE_MASK(chunk) CONVERT_TO_SIMD_MASK_TYPE(                      \
        (_mm256_movemask_epi8(_mm256_cmpeq_epi8(chunk, _mm256_set1_epi8(' '))))  |  \
        (_mm256_movemask_epi8(_mm256_cmpeq_epi8(chunk, _mm256_set1_epi8('\t')))) |  \
        (_mm256_movemask_epi8(_mm256_cmpeq_epi8(chunk, _mm256_set1_epi8('\n')))) |  \
        (_mm256_movemask_epi8(_mm256_cmpeq_epi8(chunk, _mm256_set1_epi8('\r'))))    \
    )
#else
#endif
namespace ke
{
	class FileUtil
    {
    public:
        static const char*                      findNext(const char* p, const char* end, char c) noexcept;
        static const char*                      findNameEnd(const char* p, const char* end) noexcept;
        static void                             skipWhitespace(const char*& p, const char* end) noexcept;
    public:
        static CONSTEXPR_INLINE constexpr bool  isWhitespace(char c) noexcept;
        static CONSTEXPR_INLINE constexpr bool  isNameChar(char c) noexcept;
    };
}