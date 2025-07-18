#pragma once
#include "MethodTraits.h"
#include "OptionalValue.h"

namespace ke
{
    template<typename ReturnType, typename... Args>
    class IFunctionHolder
    {
    public:
        virtual ~IFunctionHolder() = default;
        virtual ReturnType invoke(Args&&... args) = 0;
    };

    template<typename Callable, typename ReturnType, typename... Args>
    class FunctionHolder : public IFunctionHolder<ReturnType, Args...>
    {
    public:
        explicit FunctionHolder(Callable&& c);
		~FunctionHolder() override = default;

    private:
        Callable _callable;

    public:
        ReturnType invoke(Args&&... args) override;
    };

    template<typename T, typename Ret, typename... Args>
    class AutoMemberFunctionWrapper<T, Ret(T::*)(Args...)>
    {
        using MethodPtr = Ret(T::*)(Args...);

    public:
        AutoMemberFunctionWrapper(T* inst, MethodPtr m);

    private:
        T* instance;
        MethodPtr method;

    public:
        Ret operator()(Args... args) const;
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
        explicit DirtyFlaggedFunction(Callable&& callable);
        ~DirtyFlaggedFunction();

    public:
        OptionalValue<ReturnType> execute(Args... args);
        inline bool isDirty() const { return _dirty; }
        inline void setDirty() { _dirty = true; }

    private:
        bool _dirty;
        IFunctionHolder<ReturnType, Args...>* _impl;
    };
}

#include "DirtyFlaggedFunction.hpp"