#pragma once

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
}