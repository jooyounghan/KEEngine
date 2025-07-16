#pragma once
#include "HashConvertor.h"
#include <cstring>

namespace ke
{
    template<typename T>
    Hash128 HashConvertor::convertToHash(const T& value)
    {
        return computeFNV1a128(&value, sizeof(T));
    }
}