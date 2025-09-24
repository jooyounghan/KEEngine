#pragma once
#include "KEConstant.h"
#include "StaticBuffer.h"

namespace ke
{
	class ReflectParser
	{
	public:
		template<typename PropertyType>
		static KEBufferOffset parseFromString(const char* src, PropertyType& outPropertyTypes);
		template<typename PropertyType, typename ...PropertyTypes>
		static KEBufferOffset parseFromString(const char* src, PropertyType& outPropertyType, PropertyTypes&... outPropertyTypes);

	public:
		template<typename PropertyType>
		static void parseToString(IStaticBuffer* outStringBuffer, const PropertyType& property);
		template<typename PropertyType, typename ...PropertyTypes>
		static void parseToString(IStaticBuffer* outStringBuffer, const PropertyType& propertyType, const PropertyTypes&... propertyTypes);

	public:
		template<typename PropertyType>
		static KEBufferOffset parseFromBinary(const void* src, PropertyType& outPropertyTypes);
		template<typename PropertyType, typename ...PropertyTypes>
		static KEBufferOffset parseFromBinary(const void* src, PropertyType& outPropertyType, PropertyTypes&... outPropertyTypes);

	public:
		template<typename PropertyType>
		static void parseToBinary(IStaticBuffer* outBuffer, const PropertyType& property);
		template<typename PropertyType, typename ...PropertyTypes>
		static void parseToBinary(IStaticBuffer* outStringBuffer, const PropertyType& propertyType, const PropertyTypes&... propertyTypes);
	};
}
#include "ReflectParser.hpp"
