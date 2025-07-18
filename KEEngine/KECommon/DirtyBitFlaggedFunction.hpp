#pragma once
#include "DirtyBitFlaggedFunction.h"

namespace ke
{
    template<uint8 BitIndex, uint8 BitCount, typename ReturnType, typename ...Args>
    template<typename Callable>
    inline DirtyBitFlaggedFunction<BitIndex, BitCount, ReturnType, Args...>::DirtyBitFlaggedFunction(Callable&& callable, BitFlag<BitCount>& bitFlagRef)
		: _dirty(false), _bitFlagRef(bitFlagRef)
    {
        static_assert(BitIndex < BitCount, "BitIndex out of bounds for BitFlag.");
        _impl = new FunctionHolder<Callable, ReturnType, Args...>(static_cast<Callable&&>(callable));
    }

    template<uint8 BitIndex, uint8 BitCount, typename ReturnType, typename ...Args>
    inline DirtyBitFlaggedFunction<BitIndex, BitCount, ReturnType, Args...>::~DirtyBitFlaggedFunction()
    {
        delete _impl;
    }

    template<uint8 BitIndex, uint8 BitCount, typename ReturnType, typename ...Args>
    inline OptionalValue<ReturnType> DirtyBitFlaggedFunction<BitIndex, BitCount, ReturnType, Args...>::execute(Args ...args)
    {
        if constexpr (KETrait::IsVoid<ReturnType>::value)
        {
            if (_bitFlagRef.isFlagSet<BitIndex>())
            {
                _dirty = false;
                _impl->invoke(static_cast<Args&&>(args)...);
                return OptionalValue<void>();
            }
            return OptionalValue<void>(nullptr);
        }
        else
        {
            if (_bitFlagRef.isFlagSet<BitIndex>())
            {
                _dirty = false;
                return OptionalValue<ReturnType>(_impl->invoke(static_cast<Args&&>(args)...));
            }
            return OptionalValue<ReturnType>();
        }
    }

}