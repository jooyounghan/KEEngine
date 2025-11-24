#pragma once
#include "TypeCommon.h"
#include "TypeTraits.h"

namespace ke
{
    template<typename T>
    constexpr T KELimit::getMax()
    {
        if constexpr (KETrait::IsUnsigned<T>::value)
        {
            return static_cast<T>(~T(0));
        }
        else
        {
            return static_cast<T>((size_t(1) << (sizeof(T) * 8 - 1)) - 1);
        }
    }
    template<typename T>
    constexpr T KELimit::getMin()
    {
        if constexpr (KETrait::IsUnsigned<T>::value)
        {
            return static_cast<T>(0);
        }
        else
        {
            return static_cast<T>(static_cast<T>(1) << (sizeof(T) * 8 - 1));
        }
    }
}