#pragma once
namespace ke
{
	class ReflectParser
	{
	public:
		template<typename PropertyType>
		static void fromString(const char* src, size_t strlen, PropertyType* property);
		template<typename PropertyType>
		static void toString(IBuffer* dstBuffer, const PropertyType* property);

	protected:
		template<typename PropertyType>
		static void parseFromString(const char* src, size_t strlen, PropertyType* outPropertyTypes);
		template<typename PropertyType>
		static void parseToString(IBuffer* outStringBuffer, const PropertyType* property);
		template<typename PropertyType>
		static Offset parseFromBinary(const void* src, PropertyType* outPropertyTypes);
		template<typename PropertyType>
		static void parseToBinary(IBuffer* outBuffer, const PropertyType* property);
	};
}

#include "ReflectParser.hpp"
