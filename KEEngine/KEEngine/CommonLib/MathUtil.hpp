namespace ke
{
    template<typename T, typename Pred>
    constexpr const T& MathUtil::max(const T& left, const T& right, Pred pred) noexcept
    {
        return pred(left, right) ? right : left;
    }

    template<typename T>
    constexpr const T& MathUtil::max(const T& left, const T& right) noexcept
    {
        return left < right ? right : left;
    }

    template<typename T, typename Pred>
    constexpr const T& MathUtil::min(const T& left, const T& right, Pred pred) noexcept
    {
        return pred(left, right) ? right : left;
    }

    template<typename T>
    constexpr const T& MathUtil::min(const T& left, const T& right) noexcept
    {
        return left < right ? left : right;
    }

    template<typename T>
    constexpr const T& MathUtil::clamp(const T& input, const T& minLimit, const T& maxLimit) noexcept
    {
        return MathUtil::max(MathUtil::min(input, maxLimit), minLimit);
    }

    template<typename T>
    constexpr const T& MathUtil::saturate(const T& input) noexcept
    {
        return MathUtil::clamp(input, static_cast<T>(0), static_cast<T>(1));
    }

    template<typename T>
    constexpr bool MathUtil::isPowerOf2(const T& value) noexcept
    {
        STATIC_ASSERT_INTEGER_TYPE(T);
        return (value & (value - 1)) == 0;
    }

    template<typename T>
    constexpr T ke::MathUtil::getNextPowerOf2(const T& value) noexcept
    {
        STATIC_ASSERT_INTEGER_TYPE(T);
        T power = 1;
        while (power < value) power <<= 1;
        return power;
    }

    constexpr bool MathUtil::isPrime(size_t n)
    {
        if (n < 2) return false;
        for (size_t i = 2; i * i <= n; ++i)
        {
            if (n % i == 0) return false;
        }
        return true;
    }

    constexpr size_t MathUtil::nextPrime(size_t n)
    {
        while (!isPrime(++n)) {}
        return n;
    }
}
