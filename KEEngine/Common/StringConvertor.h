#pragma once
#include "MathCommon.h"
#include "OwnedString.h"
#include "StaticArray.h"

namespace ke
{
    class StringConvertor
    {
		DELETE_CONSTRUCTOR(StringConvertor);

    private:
        static StaticArray<char, 200> makeStringMap();
		static StaticArray<uint64, 19> makePower10Map();

    private:
		static void writeFixedDigitsRev(uint64 v, char*& p);

    private:
        static OwnedStringA zToString(bool isNegative, uint64 v);
		static OwnedStringA fToString(double v, size_t precision);

    public:
        template<typename T, typename ...Args>
        static OwnedStringA convertToString(const T& v, Args... args);
    };
}

#include "StringConvertor.hpp"