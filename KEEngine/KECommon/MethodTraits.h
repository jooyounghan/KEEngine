#pragma once
#include "TypeTraits.h"

#define DEFINE_METHOD_TRAIT(TraitName, MethodName)                                                                                              \
namespace KETraitDetail                                                                                                                         \
{                                                                                                                                               \
    template<typename ClassType, typename ReturnType, typename... Args>                                                                         \
    struct TraitName##Impl                                                                                                                      \
    {                                                                                                                                           \
        DELETE_CONSTRUCTOR(TraitName##Impl);                                                                                                    \
                                                                                                                                                \
    private:                                                                                                                                    \
        static TrueTrait test(decltype(static_cast<ReturnType(ClassType::*)(Args...)>(&ClassType::MethodName))*);                               \
        static FalseTrait test(...);                                                                                                            \
                                                                                                                                                \
    public:                                                                                                                                     \
        static constexpr bool condition = decltype(test(nullptr))::value;                                                                       \
    };                                                                                                                                          \
}                                                                                                                                               \
template<typename ClassType, typename ReturnType, typename... Args>  			                                                                \
struct TraitName : TraitCondition<KETraitDetail::TraitName##Impl<ClassType, ReturnType, Args...>::condition, TrueTrait, FalseTrait>::Type       \
{                                                                                                                                               \
    DELETE_CONSTRUCTOR(TraitName);                                                                                                              \
};

#define DEFINE_METHOD_TRAIT_WITH_QUALIFIER(TraitName, MethodName, Qualifier)                                                                    \
namespace KETraitDetail                                                                                                                         \
{                                                                                                                                               \
    template<typename ClassType, typename ReturnType, typename... Args>                                                                         \
    struct TraitName##Impl                                                                                                                      \
    {                                                                                                                                           \
        DELETE_CONSTRUCTOR(TraitName##Impl);                                                                                                    \
                                                                                                                                                \
    private:                                                                                                                                    \
        static TrueTrait test(decltype(static_cast<ReturnType(ClassType::*)(Args...) Qualifier>(&ClassType::MethodName))*);                     \
        static FalseTrait test(...);                                                                                                            \
                                                                                                                                                \
    public:                                                                                                                                     \
        static constexpr bool condition = decltype(test(nullptr))::value;                                                                       \
    };                                                                                                                                          \
}                                                                                                                                               \
template<typename ClassType, typename ReturnType, typename... Args>  			                                                                \
struct TraitName : TraitCondition<KETraitDetail::TraitName##Impl<ClassType, ReturnType, Args...>::condition, TrueTrait, FalseTrait>::Type       \
{                                                                                                                                               \
    DELETE_CONSTRUCTOR(TraitName);                                                                                                              \
};

#define CHECK_METHOD_TRAIT(TraitName, ClassType, ReturnType, ...) KETrait::TraitName<ClassType, ReturnType, __VA_ARGS__>::value

namespace ke
{
    template<typename T, typename MethodType>
    struct AutoMemberFunctionWrapper;

    namespace KETrait
    {
        namespace KETraitDetail
        {
            template<typename Callable, typename...Args>
            struct IsCallableImpl
            {
                DELETE_CONSTRUCTOR(IsCallableImpl);

            private:
                template<typename CallableType>
                static auto test(int) -> decltype(DeclVal<CallableType>()(DeclVal<Args>()...), TrueTrait());
                template<typename CallableType>
                static FalseTrait test(...);

            public:
                static constexpr bool condition = decltype(test<Callable>(0))::value;
            };
        }

        template<typename Callable, typename ...Args>
        struct IsCallable : TraitCondition<KETraitDetail::IsCallableImpl<Callable, Args...>::condition, TrueTrait, FalseTrait>::Type
        {
            DELETE_CONSTRUCTOR(IsCallable);
        };
    }
}