#pragma once
#include "BitFlag.h"
#include "DirtyFlaggedFunction.h"

#define ENUM_TO_INDEX(bitIndex) static_cast<uint8>(bitIndex)

namespace ke
{
    template<uint8 BitIndex, uint8 BitCount, typename ReturnType, typename... Args>
    class DirtyBitFlaggedFunction
    {
    public:
        template<typename Callable>
        DirtyBitFlaggedFunction(Callable&& callable, BitFlag<BitCount>& bitFlagRef);
        ~DirtyBitFlaggedFunction();

    public:
        OptionalValue<ReturnType> execute(Args... args);

    private:
        IFunctionHolder<ReturnType, Args...>* _impl;
		BitFlag<BitCount>& _bitFlagRef;
    };
}

#include "DirtyBitFlaggedFunction.hpp"