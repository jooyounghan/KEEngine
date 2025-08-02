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

		template<typename T>
        NODISC static constexpr T GetNextPowerOf2(const T& value) noexcept;

        NODISC static constexpr bool isPrime(size_t n);
        NODISC static constexpr size_t nextPrime(size_t n);
    };
}

#include "MathCommon.hpp"