#pragma once

#define DEFINE_METHOD_POINTER(ClassType, ReturnType, ...)                                                   \
    ReturnType(ClassType::*)(__VA_ARGS__)

#define DEFINE_HAS_METHOD(TraitName, MethodName, MethodType)                                                \
template<typename T, typename = void>                                                                       \
struct TraitName : FalseTrait {};                                                                           \
                                                                                                            \
template<typename T>                                                                                        \
struct TraitName<T, decltype((void)static_cast<MethodType>(&T::MethodName))> : TrueTrait {};

#define CHECK_HAS_METHOD(TraitName, T) TraitName<T>::value

namespace ke
{
    namespace KETrait
    {
        struct TrueTrait { static constexpr bool value = true;  using Type = TrueTrait; };
        struct FalseTrait { static constexpr bool value = false; using Type = FalseTrait; };

        template<bool Cond, typename True, typename False>
        struct TraitCondition { using Type = True; };

        template<typename True, typename False>
        struct TraitCondition<false, True, False> { using Type = False; };

        template<bool... Cond>
        struct SatisfyAll;

        template<>
        struct SatisfyAll<> : TrueTrait {};

        template<bool Head, bool... Tail>
        struct SatisfyAll<Head, Tail...>
            : TraitCondition<Head && SatisfyAll<Tail...>::value, TrueTrait, FalseTrait>::Type 
        {
        };

        template<bool... Cond>
        struct SatisfyAny;

        template<>
        struct SatisfyAny<> : FalseTrait {};

        template<bool Head, bool... Tail>
        struct SatisfyAny<Head, Tail...>
            : TraitCondition<Head || SatisfyAny<Tail...>::value, TrueTrait, FalseTrait>::Type
        {
        };

        template<bool... Cond>
        struct SatisfyNone : TraitCondition<SatisfyAny<Cond...>::value, FalseTrait, TrueTrait>::Type {};

        template<bool Cond>
        struct SatisfyNot : TraitCondition<Cond, FalseTrait, TrueTrait>::Type {};


        template<typename T>
        struct IsUnsigned
            : TraitCondition<(T(0) < T(-1)), TrueTrait, FalseTrait>::Type{};

        template<typename T>
        struct IsClass {
        private:
            template<typename C>
            static char test(int C::*);

            template<typename C>
            static int test(...);

        public:
            using Type = TraitCondition<
                sizeof(test<T>(nullptr)) == sizeof(char),
                TrueTrait,
                FalseTrait
            >::Type;

            static constexpr bool value = Type::value;
        };

        template<typename Base, typename Derived>
        struct IsBaseOf {
        private:
            static char test(Base*);
            static int  test(...);

        public:
            using Type = SatisfyAll<
                IsClass<Base>::value,
                IsClass<Derived>::value,
                sizeof(test(static_cast<Derived*>(nullptr))) == sizeof(char)
            >::Type;

            static constexpr bool value = Type::value;
        };
    };
}
