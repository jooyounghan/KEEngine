#pragma once
#include "OwnedString.h"
#include "StaticBuffer.h"

namespace ke
{
	static constexpr size_t kPropertyBinaryBufferSize = 256;

	template<typename PropertyType>
	class ReflectParser
	{
	public:
		// This Function has to be specialized
		static PropertyType ParseFromString(const char* src);
		static OwnedStringA ParseToString(const PropertyType& property);

	public:
		static PropertyType ParseFromBinary(const void* src);
		static void ParseToBinary(const PropertyType& property, StaticBuffer<kPropertyBinaryBufferSize>& outBuffer);
	};
}
#include "ReflectParser.hpp"
