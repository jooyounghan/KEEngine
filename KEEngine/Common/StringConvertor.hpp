#pragma once
#include "StringConvertor.h"

#define DEFINE_UNSIGNED_Z_CONVERTOR(Type)                               \
    template<>                                                          \
    OwnedStringA ke::StringConvertor::convertToString(const Type& v)    \
    {                                                                   \
        return zToString(false, v);                                     \
    }

#define DEFINE_SIGNED_Z_CONVERTOR(Type)                                                 \
    template<>                                                                          \
    OwnedStringA ke::StringConvertor::convertToString(const Type& v)                    \
    {                                                                                   \
        bool isNegative = (v < 0);                                                      \
        uint64_t u = isNegative ? static_cast<uint64_t>(-v) : static_cast<uint64_t>(v); \
                                                                                        \
        return zToString(isNegative, u);                                                \
    }

#define DEFINE_F_CONVERTOR(Type)                                                    \
    template<>                                                                      \
    OwnedStringA StringConvertor::convertToString(const Type& v, int precision)     \
    {                                                                               \
        return fToString(v, precision);                                             \
    }


namespace ke
{
    StaticArray<char, 200> ke::StringConvertor::makeStringMap()
    {
        StaticArray<char, 200> stringMap;
        for (uint32 i = 0; i < 100; ++i) {
            stringMap[2 * i + 0] = char('0' + (i / 10));
            stringMap[2 * i + 1] = char('0' + (i % 10));
        }
        return stringMap;
    }

    StaticArray<uint64, 19> StringConvertor::makePower10Map()
    {
		StaticArray<uint64, 19> power10Map;
        power10Map[0] = 1;
        for (uint32_t i = 1; i < 19; ++i)
        {
            power10Map[i] = power10Map[i - 1] * 10ull;
        }
        return power10Map;
    }

    void StringConvertor::writeFixedDigitsRev(uint64 v, char*& p)
    {
        static StaticArray<char, 200> stringMap = makeStringMap();

        if (v == 0)
        {
            *--p = '0';
            return;
		}

        // Read Two Digits
        while (v >= 10)
        {
            uint32 digits = (v % 100);
            v /= 100;
            p -= 2;
            memcpy(p, &stringMap[2 * digits], 2);
        }

        if (v != 0) *--p = char('0' + v);
    }

    inline OwnedStringA StringConvertor::zToString(bool isNegative, uint64 v)
    {
        char buffer[32];
        char* end = buffer + sizeof(buffer);
        char* p = end;

        writeFixedDigitsRev(v, p);

        if (isNegative) *--p = '-';
        return OwnedStringA(p, end - p);
    }

    OwnedStringA StringConvertor::fToString(double v, size_t precision)
    {
        static StaticArray<uint64, 19> power10Map = makePower10Map();

		bool isNegative = signbit(v);
        if (isnan(v)) return OwnedStringA(v < 0 ? "-nan" : "nan");
		if (isinf(v)) return OwnedStringA(v < 0 ? "-inf" : "inf");

		precision = KEMath::clamp<size_t>(precision, 1, 18);


        double intpart; 
        double frac = modf(fabs(v), &intpart); 
        uint64 ip = static_cast<uint64>(intpart);

        uint64_t pow10 = power10Map[precision];
        uint64 fracDigits = static_cast<uint64>(frac * static_cast<double>(pow10) + 0.5);

		// Handle Rounding Overflow
        if (fracDigits >= pow10)
        {
            fracDigits = 0;
            ++ip;
		}

        char buffer[64];
        char* end = buffer + sizeof(buffer);
        char* p = end;

        writeFixedDigitsRev(fracDigits + pow10, p);
        *p = '.';

        writeFixedDigitsRev(ip, p);
        if (isNegative) *--p = '-';        

        return OwnedStringA(p, end - p);
    }

    template<typename T, typename ...Args>
    OwnedStringA StringConvertor::convertToString(const T& v, Args... args)
    {
		static_assert(false, "This type is not supported as StringConvertor::convertToString.");
        return OwnedStringA();
    }

    template<>
    OwnedStringA StringConvertor::convertToString(const bool& v)
    {
		return v ? OwnedStringA("true") : OwnedStringA("false");
    }

    DEFINE_UNSIGNED_Z_CONVERTOR(uint64);
    DEFINE_UNSIGNED_Z_CONVERTOR(uint32);
    DEFINE_UNSIGNED_Z_CONVERTOR(uint16);
    DEFINE_UNSIGNED_Z_CONVERTOR(uint8);

    DEFINE_SIGNED_Z_CONVERTOR(int64);
    DEFINE_SIGNED_Z_CONVERTOR(int32);
    DEFINE_SIGNED_Z_CONVERTOR(int16);
    DEFINE_SIGNED_Z_CONVERTOR(int8);

	DEFINE_F_CONVERTOR(double);
	DEFINE_F_CONVERTOR(float);
}