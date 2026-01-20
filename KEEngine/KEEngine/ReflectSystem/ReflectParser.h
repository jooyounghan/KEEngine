#pragma once
#include "IBuffer.h"

namespace ke
{
	class ReflectParser
	{
	public:
		template<typename PropertyType>
		static Offset parseFromString(const char* src, PropertyType* outPropertyTypes);
		template<typename PropertyType, typename ...PropertyTypes>
		static Offset parseFromString(const char* src, PropertyType* outPropertyType, PropertyTypes*... outPropertyTypes);

	public:
		template<typename PropertyType>
		static void parseToString(IBuffer* outStringBuffer, const PropertyType* property);
		template<typename PropertyType, typename ...PropertyTypes>
		static void parseToString(IBuffer* outStringBuffer, const PropertyType* propertyType, const PropertyTypes*... propertyTypes);

	public:
		template<typename PropertyType>
		static Offset parseFromBinary(const void* src, PropertyType* outPropertyTypes);
		template<typename PropertyType, typename ...PropertyTypes>
		static Offset parseFromBinary(const void* src, PropertyType* outPropertyType, PropertyTypes*... outPropertyTypes);

	public:
		template<typename PropertyType>
		static void parseToBinary(IBuffer* outBuffer, const PropertyType* property);
		template<typename PropertyType, typename ...PropertyTypes>
		static void parseToBinary(IBuffer* outBuffer, const PropertyType* propertyType, const PropertyTypes*... propertyTypes);
	};
}

#include "ReflectParser.hpp"
