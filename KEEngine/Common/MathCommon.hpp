#pragma once
#include "MathCommon.h"
#include "TypeTraits.h"

namespace ke
{
    template<typename T, typename Pred>
    constexpr const T& KEMath::max(const T& left, const T& right, Pred pred) noexcept
    {
        return pred(left, right) ? right : left;
    }

    template<typename T>
    constexpr const T& KEMath::max(const T& left, const T& right) noexcept
    {
        return left < right ? right : left;
    }

    template<typename T, typename Pred>
    constexpr const T& KEMath::min(const T& left, const T& right, Pred pred) noexcept
    {
        return pred(left, right) ? right : left;
    }

    template<typename T>
    constexpr const T& KEMath::min(const T& left, const T& right) noexcept
    {
        return left < right ? left : right;
    }

    template<typename T>
    constexpr bool KEMath::isPowerOf2(const T& value) noexcept
    {
        static_assert(KETrait::IsInteger<T>::value, "T must be an integer type.");

        return (value & (value - 1)) == 0;
    }

    template<typename T>
    constexpr T ke::KEMath::getNextPowerOf2(const T& value) noexcept
    {
		static_assert(KETrait::IsInteger<T>::value, "T must be an integer type.");
        
        T power = 1;
        while (power < value) power <<= 1;
        return power;
    }

    constexpr bool KEMath::isPrime(size_t n)
    {
        if (n < 2) return false;
        for (size_t i = 2; i * i <= n; ++i) 
        {
            if (n % i == 0) return false;
        }
        return true;
    }

    constexpr size_t KEMath::nextPrime(size_t n)
    {
        while (!isPrime(++n)) {}
        return n;
    }
}