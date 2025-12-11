#pragma once

namespace ke
{
    class IBuffer;

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
    };
}

#include "StrUtil.hpp"