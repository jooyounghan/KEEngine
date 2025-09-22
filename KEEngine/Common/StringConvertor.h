#pragma once
#include "MathCommon.h"
#include "OwnedString.h"
#include "StaticArray.h"
#include "StaticBuffer.h"

namespace ke
{
    class StringConvertor
    {
		DELETE_CONSTRUCTOR(StringConvertor);

    private:
		static constexpr size_t digitCount = 20;

    private:
        static constexpr StaticArray<char, 200> makeStringMap();
		static constexpr StaticArray<uint64, digitCount> makePower10Map();

    private:
        static size_t getDecimalLength(uint64 v);

    private:
		static void writeFixedDigits(IStaticBuffer* staticBuffer, bool isNegative, uint64 v);

    private:
        static void zToStringBuffer(IStaticBuffer* staticBuffer, bool isNegative, uint64 v);
		static void fToStringBuffer(IStaticBuffer* staticBuffer, double v, size_t precision);

    public:
		template<typename T, typename ...Args>
        static void convertToString(IStaticBuffer* staticBuffer, const T& v, Args... args);
    };
}

#include "StringConvertor.hpp"