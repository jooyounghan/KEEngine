#pragma once

namespace ke
{
    namespace KETrait
    {

#pragma region Base Conditions
        struct TrueTrait 
        {
            DELETE_CONSTRUCTOR(TrueTrait);
            CONSTEXPR_INLINE static constexpr bool value = true; 
        };
        struct FalseTrait 
        {
            DELETE_CONSTRUCTOR(FalseTrait);
            CONSTEXPR_INLINE static constexpr bool value = false; 
        };

        template<bool Cond, typename True, typename False>
        struct TraitCondition 
        {
            DELETE_CONSTRUCTOR(TraitCondition);
            using Type = True; 
        };

        template<typename True, typename False>
        struct TraitCondition<false, True, False> 
        {
            DELETE_CONSTRUCTOR(TraitCondition);
            using Type = False; 
        };

        template<bool... Cond>
        struct SatisfyAll;

        template<>
        struct SatisfyAll<> : TrueTrait 
        {
            DELETE_CONSTRUCTOR(SatisfyAll);
        };

        template<bool Head, bool... Tail>
        struct SatisfyAll<Head, Tail...> : TraitCondition<Head && SatisfyAll<Tail...>::value, TrueTrait, FalseTrait>::Type 
        {
            DELETE_CONSTRUCTOR(SatisfyAll);
        };

        template<bool... Cond>
        struct SatisfyAny;

        template<>
        struct SatisfyAny<> : FalseTrait 
        {
            DELETE_CONSTRUCTOR(SatisfyAny);
        };

        template<bool Head, bool... Tail>
        struct SatisfyAny<Head, Tail...> : TraitCondition<Head || SatisfyAny<Tail...>::value, TrueTrait, FalseTrait>::Type
        {
            DELETE_CONSTRUCTOR(SatisfyAny);
        };

        template<bool... Cond>
        struct SatisfyNone : TraitCondition<SatisfyAny<Cond...>::value, FalseTrait, TrueTrait>::Type 
        {
            DELETE_CONSTRUCTOR(SatisfyNone);
        };

        template<bool Cond>
        struct SatisfyNot : TraitCondition<Cond, FalseTrait, TrueTrait>::Type 
        {
            DELETE_CONSTRUCTOR(SatisfyNot);
        };
#pragma endregion

#pragma region Type Traits
        template<typename T>
        struct IsUnsigned : TraitCondition<(T(0) < T(-1)), TrueTrait, FalseTrait>::Type
        {
            DELETE_CONSTRUCTOR(IsUnsigned);
        };

        namespace KETraitDetail
        {
            template<typename T>
            struct IsClassImpl
            {
                DELETE_CONSTRUCTOR(IsClassImpl);

            private:
                static TrueTrait test(int T::*);
                static FalseTrait test(...);

            public:
                static constexpr bool condition = decltype(test(nullptr))::value;
            };
        }

        template<typename T>
        struct IsClass : TraitCondition<KETraitDetail::IsClassImpl<T>::condition, TrueTrait, FalseTrait>::Type
        {
            DELETE_CONSTRUCTOR(IsClass);
        };

		namespace KETraitDetail
		{
            template<typename Base, typename Derived>
            struct IsBaseOfImpl
            {
                DELETE_CONSTRUCTOR(IsBaseOfImpl);

            private:
                static TrueTrait test(Base*);
                static FalseTrait  test(...);

            public:
                static constexpr bool condition = SatisfyAll<IsClass<Base>::value, IsClass<Derived>::value, decltype(test(static_cast<Derived*>(nullptr)))::value>::value;
            };
		}

        template<typename Base, typename Derived>
        struct IsBaseOf : TraitCondition<KETraitDetail::IsBaseOfImpl<Base, Derived>::condition, TrueTrait, FalseTrait>::Type 
        {
            DELETE_CONSTRUCTOR(IsBaseOf);
        };
#pragma endregion
    };
}
