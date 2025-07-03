#pragma once
#include "UtilityCommon.h"

namespace ke
{
	using uint8 = unsigned char;
	using uint16 = unsigned short;
	using uint32 = unsigned int;
	using uint64 = unsigned long long;

	struct KETrait
	{
		template<typename T>
		struct isUnsigned
		{
			static constexpr bool value = T(0) < T(-1);
		};
	};

	struct KELimit
	{
		template<typename T>
        KE_INLINE static constexpr T getMax()
        {
            if constexpr (KETrait::isUnsigned<T>::value)
            {
                return static_cast<T>(~T(0));
            }
            else
            {
                return static_cast<T>((size_t(1) << (sizeof(T) * 8 - 1)) - 1);
            }
        }

        template<typename T>
        KE_INLINE static constexpr T getMin()
        {
            if constexpr (KETrait::isUnsigned<T>::value)
            {
                return static_cast<T>(0);
            }
            else
            {
                return static_cast<T>(static_cast<T>(1) << (sizeof(T) * 8 - 1));
            }
        }
	};
}