#pragma once
#include "TypeCommon.h"

namespace ke
{
	template<uint8 BitCount>
	class BitFlag
	{
	public:
		BitFlag();

	private:
		CONSTEXPR_INLINE static constexpr uint8 getFlagBucket(const uint8 index);
		CONSTEXPR_INLINE static constexpr uint8 getTrueFlag(const uint8 index);
		CONSTEXPR_INLINE static constexpr uint8 getFalseFlag(const uint8 index);

	private:
		uint8 _flag[BitCount / 8];

	public:
		template<uint8 index>
		void setFlag();
		void setFlag(const uint8 index);

		template<uint8 index>
		void resetFlag();
		void resetFlag(const uint8 index);

		template<uint8 index>
		bool isFlagSet() const;
		bool isFlagSet(const uint8 index) const;
	};

}

#include "BitFlag.hpp"