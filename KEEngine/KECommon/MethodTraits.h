#pragma once
#include "TypeTraits.h"

#define DEFINE_METHOD_TRAIT(TraitName, MethodName)                                                                                          \
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

#define CHECK_METHOD_TRAIT(TraitName, ClassType, ReturnType, ...) KETrait::TraitName<ClassType, ReturnType, __VA_ARGS__>::value