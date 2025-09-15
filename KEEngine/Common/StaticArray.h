#pragma once
#include "LinearContainer.h"
#include "MallocAllocator.h"

namespace ke
{
    template<typename T, size_t Count>
    class StaticArray 
    {

    public:
        constexpr StaticArray();
        template<typename... Args>
        constexpr explicit StaticArray(Args... args);

    private:
        alignas(T) T _data[Count];

    public:
        constexpr size_t size() const;
        constexpr T& operator[](size_t i);
        constexpr const T& operator[](size_t i) const;
    };
}
#include "StaticArray.hpp"