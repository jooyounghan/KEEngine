#pragma once
#include "BitFlag.h"
#include "DirtyFlaggedFunction.h"

namespace ke
{
    template<uint8 BitIndex, typename ReturnType, typename... Args>
    class DirtyBitFlaggedFunction
    {
    public:
        template<typename Callable, uint8 BitCount>
        explicit DirtyBitFlaggedFunction(Callable&& callable, BitFlag<BitCount>& bitFlagRef);
        ~DirtyBitFlaggedFunction();

    public:
        ReturnType execute(Args... args);

    private:
        IFunctionHolder<ReturnType, Args...>* _impl;
		BitFlag<BitCount>& _bitFlagRef;
    };
}

#include "DirtyBitFlaggedFunction.hpp"