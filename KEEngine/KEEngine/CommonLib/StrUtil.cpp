#include "CommonLibPch.h"
#include "StrUtil.h"
#include "MathUtil.h"
#include "IBuffer.h"

#define DEFINE_UNSIGNED_Z_CONVERTOR_SPECIALIZATION(Type)                                            \
    template<>                                                                                      \
    void StrUtil::convertToStringBuffer(IBuffer* outStaticBuffer, const Type& v)      \
    {                                                                                               \
        return zToStringBuffer(outStaticBuffer, false, v);                                          \
    }

#define DEFINE_SIGNED_Z_CONVERTOR_SPECIALIZATION(Type)                                              \
    template<>                                                                                      \
    void StrUtil::convertToStringBuffer(IBuffer* outStaticBuffer, const Type& v)      \
    {                                                                                               \
        bool isNegative = (v < 0);                                                                  \
        uint64_t u = isNegative ? static_cast<uint64_t>(-v) : static_cast<uint64_t>(v);             \
                                                                                                    \
        return zToStringBuffer(outStaticBuffer, isNegative, u);                                     \
    }

#define DEFINE_F_CONVERTOR_SPECIALIZATION(Type)                                                                 \
    template<>                                                                                                  \
    void StrUtil::convertToStringBuffer(IBuffer* outStaticBuffer, const Type& v, int precision)   \
    {                                                                                                           \
        return fToStringBuffer(outStaticBuffer, v, static_cast<size_t>(precision));                             \
    }


namespace ke
{
    constexpr std::array<char, StrUtil::kStringMapCount> StrUtil::makeStringMap()
    {
        std::array<char, StrUtil::kStringMapCount> stringMap;
        for (uint32 i = 0; i < kStringMapHalfCount; ++i)
        {
            stringMap[2 * i + 0] = char('0' + (i / 10));
            stringMap[2 * i + 1] = char('0' + (i % 10));
        }
        return stringMap;
    }

    constexpr std::array<uint64, StrUtil::kDigitCount> StrUtil::makePower10Map()
    {
        std::array<uint64, StrUtil::kDigitCount> power10Map;

        power10Map[0] = 1;
        for (uint32_t i = 1; i < StrUtil::kDigitCount; ++i)
        {
            power10Map[i] = power10Map[i - 1] * 10ull;
        }
        return power10Map;
    }

    size_t StrUtil::getDecimalLength(uint64 v)
    {
        if (v == 0) return 1;

        constexpr std::array<uint64, kDigitCount> kPower10Map = makePower10Map();
        size_t low = 0;
        size_t high = kDigitCount;

        // Binary search
        while (low < high)
        {
            size_t mid = (low + high) >> 1;
            if (kPower10Map[mid] <= v)
            {
                low = mid + 1;
            }
            else
            {
                high = mid;
            }
        }
        return low;
    }

    void StrUtil::writeFixedDigits(IBuffer* staticBuffer, bool isNegative, uint64 v)
    {
        constexpr std::array<char, kStringMapCount> kStringMap = makeStringMap();
        constexpr std::array<uint64, kDigitCount> kPower10Map = makePower10Map();

        if (isNegative) staticBuffer->writeOne('-');


        if (v == 0)
        {
            staticBuffer->writeOne('0');
        }
        else
        {
            size_t decimalLength = getDecimalLength(v);
            const bool isLenghtOdd = decimalLength & 1;

            // Print leading digit if v is odd
            if (isLenghtOdd)
            {
                uint64 pow = kPower10Map[decimalLength - 1];
                uint64 leadingDigit = v / pow;
                staticBuffer->writeOne(static_cast<char>('0' + leadingDigit));
                v -= pow * leadingDigit;
                --decimalLength;
            }

            while (decimalLength > 0)
            {
                uint64_t pow = kPower10Map[decimalLength - 2];
                uint64_t digits = v / pow;

                staticBuffer->write(&kStringMap[2 * digits], 2);
                v -= pow * digits;
                decimalLength -= 2;
            }
        }

    }

    void StrUtil::zToStringBuffer(IBuffer* outStaticBuffer, bool isNegative, uint64 v)
    {
        writeFixedDigits(outStaticBuffer, isNegative, v);
    }

    void StrUtil::fToStringBuffer(IBuffer* outStaticBuffer, double v, size_t precision)
    {
        bool isNegative = signbit(v);
        if (isnan(v)) return outStaticBuffer->write(isNegative ? "-nan" : "nan", isNegative ? 4 : 3);
        if (isinf(v)) return outStaticBuffer->write(isNegative ? "-inf" : "inf", isNegative ? 4 : 3);

        constexpr std::array<uint64, kDigitCount> kPower10Map = makePower10Map();

        precision = MathUtil::clamp<size_t>(precision, 1, 18);

        double ip;
        double frac = modf(fabs(v), &ip);
        uint64 intpart = static_cast<uint64>(ip);

        uint64_t pow10 = kPower10Map[precision];
        uint64 fracAsZ = static_cast<uint64>(frac * static_cast<double>(pow10) + 0.5);

        // Handle Rounding Overflow
        if (fracAsZ >= pow10)
        {
            fracAsZ = 0;
            ++intpart;
        }
        writeFixedDigits(outStaticBuffer, isNegative, intpart);
        outStaticBuffer->writeOne('.');
        writeFixedDigits(outStaticBuffer, false, fracAsZ);
    }

    template<>
    void StrUtil::convertToStringBuffer(IBuffer* outStaticBuffer, const bool& v)
    {
        if (v) outStaticBuffer->write("true", 4);
        else outStaticBuffer->write("false", 5);
    }

    DEFINE_UNSIGNED_Z_CONVERTOR_SPECIALIZATION(uint64);
    DEFINE_UNSIGNED_Z_CONVERTOR_SPECIALIZATION(uint32);
    DEFINE_UNSIGNED_Z_CONVERTOR_SPECIALIZATION(uint16);
    DEFINE_UNSIGNED_Z_CONVERTOR_SPECIALIZATION(uint8);

    DEFINE_SIGNED_Z_CONVERTOR_SPECIALIZATION(int64);
    DEFINE_SIGNED_Z_CONVERTOR_SPECIALIZATION(int32);
    DEFINE_SIGNED_Z_CONVERTOR_SPECIALIZATION(int16);
    DEFINE_SIGNED_Z_CONVERTOR_SPECIALIZATION(int8);

    DEFINE_F_CONVERTOR_SPECIALIZATION(double);
    DEFINE_F_CONVERTOR_SPECIALIZATION(float);

    const char* StrUtil::findNext(const char* p, const char* end, char c) noexcept
    {
#if SIMD_ENABLED
        if (end - p >= SIMD_TARGET_BYTE)
        {
            const SIMD_VEC target = SIMD_SET1_EPI8(c);

            while (p + SIMD_TARGET_BYTE <= end)
            {
                SIMD_VEC chunk = SIMD_LOAD(p);
                SIMD_MASK_TYPE mask = SIMD_CMP_EPI8(chunk, target);

                if (mask)
                {
                    unsigned long index = 0;
                    SIMD_MASK_BSF(index, mask);
                    return p + index;
                }

                p += SIMD_TARGET_BYTE;
            }
        }
#endif
        while (p < end && *p != c)
            ++p;
        return p;
    }

    const char* StrUtil::findNameEnd(const char* p, const char* end) noexcept
    {
        while (p < end && StrUtil::isNameChar(*p)) ++p;
        return p;
    }

    CONSTEXPR_INLINE constexpr bool StrUtil::isWhitespace(char c) noexcept
    {
        return c == ' ' || c == '\t' || c == '\r' || c == '\n';
    }

    CONSTEXPR_INLINE constexpr bool StrUtil::isNameChar(char c) noexcept
    {
        return (c >= 'A' && c <= 'Z')
            || (c >= 'a' && c <= 'z')
            || (c >= '0' && c <= '9')
            || c == ':' || c == '_' || c == '-';
    }

    const char* StrUtil::findSequence(const char* p, const char* end, const char* seq, size_t seqLen) noexcept
    {
        if (seqLen == 0) return p;
        if (p >= end) return end;
        if (seqLen == 1) return findNext(p, end, seq[0]);

        const char first = seq[0];
        const char* cur = p;

#if SIMD_ENABLED
        // SIMD 블록 단위로 첫 문자 위치 탐색
        if (end - cur >= SIMD_TARGET_BYTE)
        {
            SIMD_VEC target = SIMD_SET1_EPI8(first);
            while (cur + SIMD_TARGET_BYTE <= end)
            {
                SIMD_VEC chunk = SIMD_LOAD(cur);
                SIMD_MASK_TYPE mask = SIMD_CMP_EPI8(chunk, target);
                if (mask)
                {
                    // 마스크에 설정된 모든 비트(인덱스) 검사
                    while (mask)
                    {
                        unsigned long idx = 0;
                        SIMD_MASK_BSF(idx, mask);
                        const char* pos = cur + idx;
                        // 남은 길이 확인
                        if (static_cast<size_t>(end - pos) < seqLen) return end;
                        if (std::memcmp(pos, seq, seqLen) == 0) return pos;
                        // 가장 낮은 비트 제거
                        mask &= (mask - 1);
                    }
                }
                cur += SIMD_TARGET_BYTE;
            }
        }
#endif
        while (true)
        {
            // memchr requires length; cast away const for API but keep pointer arithmetic safe
            size_t remaining = static_cast<size_t>(end - cur);
            if (remaining == 0) return end;
            const void* found = std::memchr(cur, first, remaining);
            if (found == nullptr) return end;
            cur = static_cast<const char*>(found);
            // ensure enough room for full sequence
            if (static_cast<size_t>(end - cur) < seqLen) return end;
            if (std::memcmp(cur, seq, seqLen) == 0) return cur;
            ++cur; // continue searching after this position
        }
    }

    void StrUtil::skipWhitespace(const char*& p, const char* end) noexcept
    {
#if SIMD_ENABLED
        while (end - p >= SIMD_TARGET_BYTE)
        {

            SIMD_VEC chunk = SIMD_LOAD(p);
            SIMD_MASK_TYPE mask = SIMD_WHITESPACE_MASK(chunk);

            if (mask == SIMD_ALL_ONES_MASK)
            {
                p += SIMD_TARGET_BYTE;
                continue;
            }
            break;
        }
#endif
        while (p < end && StrUtil::isWhitespace(*p))
            ++p;
    }
}