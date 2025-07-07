#pragma once

namespace ke
{
    struct KETrait
    {
        template<typename T>
        struct IsUnsigned
        {
            static constexpr bool value = T(0) < T(-1);
        };

        template<typename T>
        struct IsClass
        {
        private:
            template <typename C>
            static char test(int C::*);
            template <typename C>
            static int test(...);

        public:
            static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(char);
        };

        template<typename Base, typename Derived>
        struct IsBaseOf
        {
        private:
            static char test(Base*);
            static int test(...);

        public:
            static constexpr bool value =
                IsClass<Base>::value
                && IsClass<Derived>::value
                && sizeof(test(static_cast<Derived*>(nullptr))) == sizeof(char);
        };
    };
}
