#pragma once
#include "MethodTraits.h"

namespace ke
{
    template<typename ReturnType, typename... Args>
    struct IFunctionHolder
    {
        virtual ~IFunctionHolder() = default;
        virtual ReturnType invoke(Args&&... args) = 0;
    };

    template<typename Callable, typename ReturnType, typename... Args>
    struct FunctionHolder : IFunctionHolder<ReturnType, Args...>
    {
        Callable _callable;

        explicit FunctionHolder(Callable&& c) : _callable(static_cast<Callable&&>(c)) {}

        ReturnType invoke(Args&&... args) override
        {
            static_assert(ke::KETrait::IsCallable<Callable, Args...>::value,
				"Callable must be a valid callable type with the provided arguments.");
            return _callable(static_cast<Args&&>(args)...);
        }
    };

    template<typename T, typename Ret, typename... Args>
    struct AutoMemberFunctionWrapper<T, Ret(T::*)(Args...)>
    {
        using MethodPtr = Ret(T::*)(Args...);

        T* instance;
        MethodPtr method;

        AutoMemberFunctionWrapper(T* inst, MethodPtr m) : instance(inst), method(m) {}

        Ret operator()(Args... args) const
        {
            return (instance->*method)(static_cast<Args&&>(args)...);
        }
    };

    template<typename T, typename Ret, typename... Args>
    AutoMemberFunctionWrapper<T, Ret(T::*)(Args...)>
        BindMember(T* instance, Ret(T::* method)(Args...))
    {
        return AutoMemberFunctionWrapper<T, Ret(T::*)(Args...)>(instance, method);
    }

    template<typename ReturnType, typename... Args>
    class DirtyFlaggedFunction
    {
    public:
        template<typename Callable>
        explicit DirtyFlaggedFunction(Callable&& callable)
            : _dirty(false)
        {
            _impl = new FunctionHolder<Callable, ReturnType, Args...>(static_cast<Callable&&>(callable));
        }

        ~DirtyFlaggedFunction()
        {
            delete _impl;
        }

        ReturnType execute(Args... args)
        {
            if (_dirty)
            {
                _dirty = false;
                return _impl->invoke(static_cast<Args&&>(args)...);
            }
        }

        inline bool isDirty() const { return _dirty; }
        inline void setDirty() { _dirty = true; }

    private:
        bool _dirty;
        IFunctionHolder<ReturnType, Args...>* _impl;
    };
}

#include "DirtyFlaggedFunction.hpp"