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
        NODISC static constexpr const T& clamp(const T& input, const T& min, const T& max) noexcept;

        template<typename T>
        NODISC static constexpr const T& saturate(const T& input) noexcept;

        template<typename T>
        NODISC static constexpr bool isPowerOf2(const T& value) noexcept;

		template<typename T>
        NODISC static constexpr T getNextPowerOf2(const T& value) noexcept;

        NODISC static constexpr bool isPrime(size_t n);
        NODISC static constexpr size_t nextPrime(size_t n);
    };
}

#include "MathCommon.hpp"