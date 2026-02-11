#pragma once
#include "IBuffer.h"

namespace ke
{
	class ReflectParser
	{
	public:
		template<typename PropertyType>
		static void parseFromString(const char* src, size_t strlen, PropertyType* outPropertyTypes);

	public:
		template<typename PropertyType>
		static void parseToString(IBuffer* outStringBuffer, const PropertyType* property);

	public:
		template<typename PropertyType>
		static Offset parseFromBinary(const void* src, PropertyType* outPropertyTypes);

	public:
		template<typename PropertyType>
		static void parseToBinary(IBuffer* outBuffer, const PropertyType* property);
	};
}

#include "ReflectParser.hpp"
