#pragma once

namespace ke
{
    class IBuffer;

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

    struct StrUtil
    {
    private:
        static constexpr size_t kStringMapCount = 200;
        static constexpr size_t kStringMapHalfCount = kStringMapCount / 2;
        static constexpr size_t kDigitCount = 20;

    private:
        static constexpr std::array<char, kStringMapCount> makeStringMap();
        static constexpr std::array<uint64, kDigitCount> makePower10Map();

    private:
        static size_t getDecimalLength(uint64 v);

    private:
        static void writeFixedDigits(IBuffer* outStaticBuffer, bool isNegative, uint64 v);

    private:
        static void zToStringBuffer(IBuffer* outStaticBuffer, bool isNegative, uint64 v);
        static void fToStringBuffer(IBuffer* outStaticBuffer, double v, size_t precision);

    public:
        template<typename T, typename ...Args>
        static void convertToStringBuffer(IBuffer* outStaticBuffer, const T& v, Args... args);

    public:
        static const char*  findNext(const char* p, const char* end, char c) noexcept;
        static const char*  findNameEnd(const char* p, const char* end) noexcept;
        static const char*  findSequence(const char* p, const char* end, const char* seq, size_t seqLen) noexcept;
        static void         skipWhitespace(const char*& p, const char* end) noexcept;

    public:
        static CONSTEXPR_INLINE constexpr bool  isWhitespace(char c) noexcept;
        static CONSTEXPR_INLINE constexpr bool  isNameChar(char c) noexcept;

    };
}

#include "StrUtil.hpp"