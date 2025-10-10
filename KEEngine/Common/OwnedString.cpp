#include "OwnedString.h"

namespace ke
{
	template<>
	size_t HashGenerator<OwnedStringA>::convertToHash(const OwnedStringA& value)
	{
		return computeHash(value.c_str(), value.length());
	}
}