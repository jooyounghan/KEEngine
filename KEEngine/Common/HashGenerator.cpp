#include "HashGenerator.h"

#define DEFINE_RAW_VALUE_HASH_SPECIALIZATION(Raw)						\
template<>                                                              \
size_t HashGenerator<Raw>::convertToHash(const Raw& value)	            \
{																		\
	return computeHash(&value, sizeof(value));							\
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
}