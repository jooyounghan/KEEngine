#pragma once
#include "DirtyBitFlaggedFunction.h"

namespace ke
{
    template<uint8 BitIndex, typename ReturnType, typename ...Args>
    template<typename Callable, uint8 BitCount>
    inline DirtyBitFlaggedFunction<BitIndex, ReturnType, Args...>::DirtyBitFlaggedFunction(Callable&& callable, BitFlag<BitCount>& bitFlagRef)
		: _dirty(false), _bitFlagRef(bitFlagRef)
    {
        static_assert(BitIndex < BitCount, "BitIndex out of bounds for BitFlag.");
        _impl = new FunctionHolder<Callable, ReturnType, Args...>(static_cast<Callable&&>(callable));
    }

    template<uint8 BitIndex, typename ReturnType, typename ...Args>
    inline DirtyBitFlaggedFunction<BitIndex, ReturnType, Args...>::~DirtyBitFlaggedFunction()
    {
        delete _impl;
    }

    template<uint8 BitIndex, typename ReturnType, typename ...Args>
    inline ReturnType DirtyBitFlaggedFunction<BitIndex, ReturnType, Args...>::execute(Args ...args)
    {
        if constexpr (_bitFlagRef.isFlagSet<BitIndex>())
        {
            _dirty = false;
            return _impl->invoke(static_cast<Args&&>(args)...);
        }
    }

}