#pragma once
#include "MathCommon.h"
#include "TypeTraits.h"

namespace ke
{
    template<typename T, typename Pred>
    NODISC constexpr const T& KEMath::max(const T& left, const T& right, Pred pred) noexcept
    {
        return pred(left, right) ? right : left;
    }

    template<typename T>
    NODISC constexpr const T& KEMath::max(const T& left, const T& right) noexcept
    {
        return left < right ? right : left;
    }

    template<typename T, typename Pred>
    NODISC constexpr const T& KEMath::min(const T& left, const T& right, Pred pred) noexcept
    {
        return pred(left, right) ? right : left;
    }

    template<typename T>
    NODISC constexpr const T& KEMath::min(const T& left, const T& right) noexcept
    {
        return left < right ? left : right;
    }
    template<typename T>
    inline constexpr NODISC T ke::KEMath::GetNextPowerOf2(const T& value) noexcept
    {
		static_assert(KETrait::IsInteger<T>::value, "T must be an integer type.");
        
        T power = 1;
        while (power < value) power <<= 1;
        return power;
    }
}