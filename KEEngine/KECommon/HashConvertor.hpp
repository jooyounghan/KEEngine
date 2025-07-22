#include "HashConvertor.h"

namespace ke
{
    template<typename T>
    Hash128 HashConvertor::convertToHash(const T& value)
    {
        return computeHash(&value, sizeof(T));
    }
}

