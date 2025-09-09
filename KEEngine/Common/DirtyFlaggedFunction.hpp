#pragma once
#include "DirtyFlaggedFunction.h"

namespace ke
{
	template<typename Callable, typename ReturnType, typename ...Args>
	FunctionHolder<Callable, ReturnType, Args...>::FunctionHolder(Callable&& c) : _callable(static_cast<Callable&&>(c)) {}

    template<typename Callable, typename ReturnType, typename ...Args>
    ReturnType FunctionHolder<Callable, ReturnType, Args...>::invoke(Args && ...args)
    {
        static_assert(ke::KETrait::IsCallable<Callable, Args...>::value,
            "Callable does not satisfy the required IsCallable Trait.");
        return _callable(static_cast<Args&&>(args)...);
    }

    template<typename T, typename Ret, typename ...Args>
    AutoMemberFunctionWrapper<T, Ret(T::*)(Args...)>::AutoMemberFunctionWrapper(T* inst, MethodPtr m) : instance(inst), method(m) {}

    template<typename T, typename Ret, typename... Args>
    Ret AutoMemberFunctionWrapper<T, Ret(T::*)(Args...)>::operator()(Args... args) const
    {
        return (instance->*method)(static_cast<Args&&>(args)...);
    }
    
    template<typename ReturnType, typename ...Args>
    template<typename Callable>
    DirtyFlaggedFunction<ReturnType, Args...>::DirtyFlaggedFunction(Callable&& callable)
        : _dirty(false)
    {
        _impl = new FunctionHolder<Callable, ReturnType, Args...>(static_cast<Callable&&>(callable));
    }

    template<typename ReturnType, typename ...Args>
    DirtyFlaggedFunction<ReturnType, Args...>::~DirtyFlaggedFunction()
    {
		KEMemory::SafeRelease(_impl);
    }

    template<typename ReturnType, typename ...Args>
    OptionalValue<ReturnType> DirtyFlaggedFunction<ReturnType, Args...>::execute(Args ...args)
    {
        if constexpr (KETrait::IsVoid<ReturnType>::value)
        {
            if (_dirty)
            {
                _dirty = false;
                _impl->invoke(static_cast<Args&&>(args)...);
                return OptionalValue<void>();
            }
            return OptionalValue<void>(nullptr);
        }
        else
        {
            if (_dirty)
            {
                _dirty = false;
                return OptionalValue<ReturnType>(_impl->invoke(static_cast<Args&&>(args)...));
            }
            return OptionalValue<ReturnType>();
        }
    }
}