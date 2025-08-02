#pragma once
#include "UtilityCommon.h"

namespace ke
{
    struct KELimit
    {
        template<typename T>
        CONSTEXPR_INLINE static constexpr T getMax();

        template<typename T>
        CONSTEXPR_INLINE static constexpr T getMin();
    };
}

#include "TypeLimit.hpp"