#pragma once

namespace ke
{
    namespace KETrait
    {

#pragma region Base Conditions
        struct TrueTrait { CONSTEXPR_INLINE static constexpr bool value = true; };
        struct FalseTrait { CONSTEXPR_INLINE static constexpr bool value = false; };

        template<bool Cond, typename True, typename False>
        struct TraitCondition { using Type = True; };

        template<typename True, typename False>
        struct TraitCondition<false, True, False> { using Type = False; };

        template<bool... Cond>
        struct SatisfyAll;

        template<>
        struct SatisfyAll<> : TrueTrait 
        {
        };

        template<bool Head, bool... Tail>
        struct SatisfyAll<Head, Tail...> : TraitCondition<Head && SatisfyAll<Tail...>::value, TrueTrait, FalseTrait>::Type 
        {
        };

        template<bool... Cond>
        struct SatisfyAny;

        template<>
        struct SatisfyAny<> : FalseTrait {};

        template<bool Head, bool... Tail>
        struct SatisfyAny<Head, Tail...> : TraitCondition<Head || SatisfyAny<Tail...>::value, TrueTrait, FalseTrait>::Type
        {
        };

        template<bool... Cond>
        struct SatisfyNone : TraitCondition<SatisfyAny<Cond...>::value, FalseTrait, TrueTrait>::Type 
        {
        };

        template<bool Cond>
        struct SatisfyNot : TraitCondition<Cond, FalseTrait, TrueTrait>::Type 
        {
        };
#pragma endregion

#pragma region Type Traits
        template<typename T>
        struct IsUnsigned : TraitCondition<(T(0) < T(-1)), TrueTrait, FalseTrait>::Type
        {
        };

        template<typename T>
        struct IsClassImpl 
        {
            template<typename C>
            static TrueTrait test(int C::*);

            template<typename C>
            static FalseTrait test(...);
            
            static constexpr bool condition = decltype(test<T>(nullptr))::value;
        };

        template<typename T>
        struct IsClass : TraitCondition<IsClassImpl<T>::condition, TrueTrait, FalseTrait>::Type 
        {
        };

        template<typename Base, typename Derived>
        struct IsBaseOfImpl 
        {
            static TrueTrait test(Base*);

            static FalseTrait  test(...);

            static constexpr bool condition = SatisfyAll<IsClass<Base>::value, IsClass<Derived>::value, decltype(test(static_cast<Derived*>(nullptr)))::value>::value;
        };

        template<typename Base, typename Derived>
        struct IsBaseOf : TraitCondition<IsBaseOfImpl<Base, Derived>::condition, TrueTrait, FalseTrait>::Type 
        {
        };
#pragma endregion

#pragma region Method Traits
        //template<typename Unused, typename T>
        //struct HasMethodImpl : FalseTrait {};

        //template<typename ClassType, typename ReturnType, typename... Args>
        //struct HasMethodImpl<ClassType, ReturnType(ClassType::*)(Args...)>
        //{
        //private:
        //    template<typename U>
        //    static TrueTrait test(U* u) -> decltype(static_cast<ReturnType(U::*)(Args...)>(&U::operator()), TrueTrait{} );

        //    template<typename>
        //    static FalseTrait test(...);

        //public:
        //    static constexpr bool value = decltype(test<ClassType>(nullptr))::value;
        //};

        //template<typename ClassType, typename ReturnType, typename... Args>
        //struct HasMethod : HasMethodImpl<ClassType, ReturnType(ClassType::*)(Args...)>::Type 
        //{
        //};
#pragma endregion

    };
}
