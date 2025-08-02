#pragma once
#include "DirtyBitFlaggedFunction.h"

namespace ke
{
    template<uint8 BitIndex, uint8 BitCount, typename ReturnType, typename ...Args>
    template<typename Callable>
    DirtyBitFlaggedFunction<BitIndex, BitCount, ReturnType, Args...>::DirtyBitFlaggedFunction(Callable&& callable, BitFlag<BitCount>& bitFlagRef)
		: _bitFlagRef(bitFlagRef)
    {
        static_assert(BitIndex < BitCount, "BitIndex out of bounds for BitFlag.");
        _impl = new FunctionHolder<Callable, ReturnType, Args...>(static_cast<Callable&&>(callable));
    }

    template<uint8 BitIndex, uint8 BitCount, typename ReturnType, typename ...Args>
    DirtyBitFlaggedFunction<BitIndex, BitCount, ReturnType, Args...>::~DirtyBitFlaggedFunction()
    {
        delete _impl;
    }

    template<uint8 BitIndex, uint8 BitCount, typename ReturnType, typename ...Args>
    OptionalValue<ReturnType> DirtyBitFlaggedFunction<BitIndex, BitCount, ReturnType, Args...>::execute(Args ...args)
    {
		bool isDirty = _bitFlagRef.isFlagSet<BitIndex>();
        if constexpr (KETrait::IsVoid<ReturnType>::value)
        {
            if (isDirty)
            {
				_bitFlagRef.resetFlag<BitIndex>();
                _impl->invoke(static_cast<Args&&>(args)...);
                return OptionalValue<void>();
            }
            return OptionalValue<void>(nullptr);
        }
        else
        {
            if (isDirty)
            {
                _bitFlagRef.resetFlag<BitIndex>();
                return OptionalValue<ReturnType>(_impl->invoke(static_cast<Args&&>(args)...));
            }
            return OptionalValue<ReturnType>();
        }
    }

}