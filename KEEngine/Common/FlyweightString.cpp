#include "FlyweightString.h"

namespace ke
{
	template<>
	size_t HashGenerator<FlyweightStringA>::convertToHash(const FlyweightStringA& value)
	{
		return value.getEntryIndex();
	}
}