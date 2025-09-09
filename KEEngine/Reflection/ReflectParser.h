#pragma once
#include "OwnedString.h"

namespace ke
{
	template<typename PropertyType>
	class ReflectParser
	{
	public:
		// This Function has to be specialized
		static PropertyType ParseFromString(const char* src) = delete;
		static OwnedStringA ParseToString(const PropertyType& property) = delete;
	};
}
