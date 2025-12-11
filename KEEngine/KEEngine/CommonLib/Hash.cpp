#include "CommonLibPch.h"
#include "Hash.h"

#define DEFINE_RAW_VALUE_HASH_SPECIALIZATION(Raw)	\
template<>                                          \
size_t Hash<Raw>::convertToHash(const Raw& value)	\
{													\
	return computeHash(&value, sizeof(value));		\
}

namespace ke
{
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(bool);
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(uint64);
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(uint32);
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(uint16);
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(uint8);
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(int64);
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(int32);
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(int16);
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(int8);
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(double);
    DEFINE_RAW_VALUE_HASH_SPECIALIZATION(float);


    // std
    template<>
    size_t Hash<std::basic_string_view<char>>::convertToHash(const std::basic_string_view<char>& stringView)
    {
        return computeHash(stringView.data(), stringView.length());
    }

    template<>
    size_t Hash<std::basic_string_view<wchar_t>>::convertToHash(const std::basic_string_view<wchar_t>& stringView)
    {
        return computeHash(stringView.data(), stringView.length() * sizeof(wchar_t));
    }
}