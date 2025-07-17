#pragma once
#include "DirtyFlaggedFunction.h"

namespace ke
{
	template<typename Callable, typename ReturnType, typename ...Args>
	inline FunctionHolder<Callable, ReturnType, Args...>::FunctionHolder(Callable&& c) : _callable(static_cast<Callable&&>(c)) {}

    template<typename Callable, typename ReturnType, typename ...Args>
    inline ReturnType FunctionHolder<Callable, ReturnType, Args...>::invoke(Args && ...args)
    {
        static_assert(ke::KETrait::IsCallable<Callable, Args...>::value,
            "Callable does not satisfy the required IsCallable Trait.");
        return _callable(static_cast<Args&&>(args)...);
    }

    template<typename T, typename Ret, typename ...Args>
    inline AutoMemberFunctionWrapper<T, Ret(T::*)(Args...)>::AutoMemberFunctionWrapper(T* inst, MethodPtr m) : instance(inst), method(m) {}

    template<typename T, typename Ret, typename... Args>
    inline Ret AutoMemberFunctionWrapper<T, Ret(T::*)(Args...)>::operator()(Args... args) const
    {
        return (instance->*method)(static_cast<Args&&>(args)...);
    }
    
    template<typename ReturnType, typename ...Args>
    template<typename Callable>
    inline DirtyFlaggedFunction<ReturnType, Args...>::DirtyFlaggedFunction(Callable&& callable)
        : _dirty(false)
    {
        _impl = new FunctionHolder<Callable, ReturnType, Args...>(static_cast<Callable&&>(callable));
    }

    template<typename ReturnType, typename ...Args>
    inline DirtyFlaggedFunction<ReturnType, Args...>::~DirtyFlaggedFunction()
    {
        delete _impl;
    }

    template<typename ReturnType, typename ...Args>
    inline ReturnType DirtyFlaggedFunction<ReturnType, Args...>::execute(Args ...args)
    {
        if (_dirty)
        {
            _dirty = false;
            return _impl->invoke(static_cast<Args&&>(args)...);
        }
    }
}