#pragma once
#include "BitFlag.h"
#include <cstdlib>

namespace ke
{
	template<uint8 BitCount>
	BitFlag<BitCount>::BitFlag()
	{
		memset(_flag, 0, sizeof(_flag));
	}

	template<uint8 BitCount>
	template<uint8 index>
	inline void BitFlag<BitCount>::setFlag()
	{
		static_assert(index < BitCount, "Index out of bounds for BitFlag.");
		_flag[getFlagBucket(index)] |= getTrueFlag(index);
	}

	template<uint8 BitCount>
	void BitFlag<BitCount>::setFlag(uint8 index) 
	{ 
		if (index < BitCount)
		{
			_flag[getFlagBucket(index)] |= getTrueFlag(index);
		}
	}

	template<uint8 BitCount>
	template<uint8 index>
	inline void BitFlag<BitCount>::resetFlag()
	{
		static_assert(index < BitCount, "Index out of bounds for BitFlag.");
		_flag[getFlagBucket(index)] &= getFalseFlag(index);
	}

	template<uint8 BitCount>
	void BitFlag<BitCount>::resetFlag(uint8 index) 
	{ 
		if (index < BitCount)
		{
			_flag[getFlagBucket(index)] &= getFalseFlag(index);
		}
	}

	template<uint8 BitCount>
	template<uint8 index>
	inline bool BitFlag<BitCount>::isFlagSet() const
	{
		static_assert(index < BitCount, "Index out of bounds for BitFlag.");
		return _flag[getFlagBucket(index)] & getTrueFlag(index);
	}

	template<uint8 BitCount>
	bool BitFlag<BitCount>::isFlagSet(uint8 index) const 
	{ 
		if (index < BitCount)
		{
			return _flag[getFlagBucket(index)] & getTrueFlag(index);
		}
		return false;
	}
}