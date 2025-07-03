#pragma once
#include "UtilityCommon.h"

namespace ke
{
    struct KEMath
    {
        template<typename T, typename Pred>
        NODISC static constexpr const T& max(const T& left, const T& right, Pred pred) noexcept;

        template<typename T>
        NODISC static constexpr const T& max(const T& left, const T& right) noexcept;

        template<typename T, typename Pred>
        NODISC static constexpr const T& min(const T& left, const T& right, Pred pred) noexcept;

        template<typename T>
        NODISC static constexpr const T& min(const T& left, const T& right) noexcept;
    };
}

#include "MathCommon.hpp"