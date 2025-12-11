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
}